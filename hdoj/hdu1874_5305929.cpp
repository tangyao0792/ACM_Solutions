/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>

const int INF = 100000000;
int n, m;
int w[210][210];

void Floyd();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while( scanf("%d %d", &n, &m)>0)
    {
        for(int i = 0; i < 210; i++)
        {
            for(int j = 0; j < 210; j++)
            {
                w[i][j] = INF;
            }
        }
        for(int i = 0; i < 210; i++)
        {
            w[i][i] = 0;
        }
        for(int i = 0; i < m; i++)
        {
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            if(w[a][b] > c)      w[a][b] = w[b][a] = c;
        }
        Floyd();
        int x, y;
        scanf("%d %d",&x,&y);
        if(w[x][y] < INF)
        {
            printf("%d\n", w[x][y]);
        }
        else
        {
            printf("-1\n");
        }
    }
}

void Floyd()
{
    for(int k = 0; k < n; k++)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
            {
                if(w[i][j] >w[i][k]+w[k][j])
                {
                    w[i][j] = w[i][k]+w[k][j];
                }
            }
}
