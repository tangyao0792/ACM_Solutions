#include<iostream>
#include<cstring>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

int n, m;
int cnt;
int g[1010][1010];
int vis[1010];
int d[1010];
bool flag;

void dfs(int cur, int t);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase, i, j, x, y, w;
    cin >> nCase;
    while(nCase--)
    {
        memset(g, 0, sizeof(g));
        memset(vis, 0, sizeof(vis));
        memset(d, 0, sizeof(d));
        cin >> n >> m;
        for(i = 0; i < m; i++)
        {
            cin >> x >> y >> w;
            g[x][y] = w;
        }
        flag = false;
        cnt = 0;
        for(i = 0; i < n && !flag; i++)
        {
            for(j = 0; j < n && !flag; j++)
            {
                if(g[i][j])
                {
                    cnt++;
                    vis[i] = cnt;
                    d[i] = 0;
                    dfs(j, 0+g[i][j]);
                }
            }
        }
        if(flag)
        {
            cout << "possible" << endl;
        }
        else
        {
            cout << "not possible" << endl;
        }
    }
    return 0;
}

void dfs(int cur, int t)
{
    if(vis[cur] == cnt)
    {
        if(t < d[cur])
        {
            flag = true;
        }
        return;
    }
    d[cur] = t;
    vis[cur] = cnt;
    int i;
    for(i = 0; i < n && !flag; i++)
    {
        if( g[cur][i])
        {
            dfs(i, t+g[cur][i]);
        }
    }
}
