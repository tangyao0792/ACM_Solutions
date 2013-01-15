/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

int p[1100];

int find(int x);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int n, m;
    while(scanf("%d %d", &n, &m) && n)
    {
        for(int i = 0; i < 1100; i++)
        {
            p[i] = i;
        }
        int cnt = 0;
        for(int i = 0; i < m; i++)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            int px = find(x);
            int py = find(y);
            if(px != py)
            {
                cnt++;
                p[px] = py;
            }
        }
        int ans = n-1-cnt;
        if(ans>=0)
        {
            printf("%d\n", n-1-cnt);
        }
        else
        {
            printf("0\n");
        }
    }
    return 0;
}

int find(int x)
{
    return p[x]==x?x:(p[x]=find(p[x]));
}
