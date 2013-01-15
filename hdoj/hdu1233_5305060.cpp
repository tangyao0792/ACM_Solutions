/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>
const int INF = 1<<28;
int n, m;
int g[110][110],lowc[110], vis[110];
int prim();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d", &n) && n)
    {
        m = (n-1)*n/2;
        for(int i = 0; i < m; i++)
        {
            int x, y, w;
            scanf("%d %d %d",&x,&y,&w);
            g[x][y] = g[y][x] = w;
        }
        printf("%d\n",prim());
    }
    return 0;
}

int prim()
{
    memset(vis, 0, sizeof(vis));
    for(int i = 2; i <= n; i++)
    {
        lowc[i] = g[1][i];
    }
    int ans = 0;
    lowc[1] = 0;
    vis[1] = 1;
    for(int i = 0; i < n-1; i++)
    {
        int mindis = INF;
        int minone;
        for(int j = 1; j <= n; j++)
        {
            if( !vis[j] && mindis>lowc[j])
            {
                mindis = lowc[j];
                minone = j;
            }
        }
        ans += lowc[minone];
        vis[minone] = 1;
        for(int j = 1; j <= n; j++)
        {
            if( !vis[j] && lowc[j] > g[minone][j])
            {
                lowc[j] = g[minone][j];
            }
        }
    }
    return ans;
}
