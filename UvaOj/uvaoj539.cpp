#include<iostream>
#include<cstring>

#ifndef ONLINE_JUDGE
    #include<stdio.h>
#endif

using namespace std;

int n, m, nMax, nLen;
int g[30][30], vis[30][30];

void dfs(int x);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int i, j, x, y;
    while(cin >> n >> m)
    {
        if(n == 0 && m == 0)
        {
            break;
        }
        memset(g, 0, sizeof(int) * 30 * 30);
        memset(vis, 0, sizeof(int) * 30 * 30);

        for(i = 0; i < m; i++)
        {
            cin >> x >> y;
            g[x][y] = g[y][x] = 1;
        }
        nMax = 0;
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < n; j++)
            {
                if(g[i][j] == 1)
                {
                    nLen = 1;
                    vis[i][j] = vis[j][i] = 1;
                    dfs(j);
                    vis[i][j] = vis[j][i] = 0;
                }
            }
        }
        cout << nMax << endl;
    }
    return 0;
}

void dfs(int x)
{
    int i;
    for(i = 0; i < n; i++)
    {
        if(g[x][i] == 1 && vis[x][i] == 0)
        {
            vis[x][i] = vis[i][x] = 1;
            nLen++;
            dfs(i);
            nLen--;
            vis[x][i] = vis[i][x] = 0;
        }
    }
    if(nLen > nMax)
    {
        nMax = nLen;
    }
}
