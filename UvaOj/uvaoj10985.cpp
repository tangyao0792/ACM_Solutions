#include<iostream>
#include<cstring>
#define INF 1000

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

int g[130][130];
int d[130][130];
int vis[130];
int n, m,cnt, nMax;

void Floyd();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase;
    cin >> nCase;
    for(int i = 1; i <= nCase; i++)
    {
        memset(g, 0, sizeof(g));
        for(int j = 0; j < 130; j++)
        {
            for(int k = 0; k < 130; k++)
            {
                d[j][k] = INF;
            }
        }

        cout << "Case #"<<i<<": ";
        cin >> n >> m;
        for(int j = 0; j < m; j++)
        {
            int x, y;
            cin >> x >> y;
            d[x][y] = d[y][x]=g[x][y] = g[y][x]=1;

        }
        Floyd();

        nMax = 0;
        for(int j = 0; j < n; j++)
        {
            d[j][j] = 0;
        }
        for(int j = 0; j < n; j++)
        {
            for(int k = 0; k < j; k++)
            {
                memset(vis,0,sizeof(vis));
                for(int l = 0; l < n && d[j][k] != INF; l++)
                {
                    if(d[j][l]+d[l][k] == d[j][k])
                    {
                        vis[l]=1;
                    }
                }
                cnt = 0;
                for(int x = 0; x < n; x++)
                {
                    for(int y = 0; y < x && vis[x];y++)
                    {
                        if(vis[y] && d[j][x] != d[j][y]&&g[x][y])cnt++;
                    }
                }
                nMax = max(nMax, cnt);
            }
        }

        cout << nMax<<endl;
    }
    return 0;
}

void Floyd()
{
    for(int k = 0; k < n; k++)
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(d[i][j] > d[i][k]+d[k][j]&&i!=j)
                {
                    d[i][j]=d[i][k]+d[k][j];
                }
            }
        }
    }
}
