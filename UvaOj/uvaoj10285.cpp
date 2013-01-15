#include<iostream>
#include<cstring>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

int r, c;
int a[110][110];
int d[110][110];
int vis[110][110];
int dx[4] = { 0, 0, -1, 1};
int dy[4] = { 1, -1, 0, 0};
int dp(int x, int y);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase, i, j, nMax;
    cin >> nCase;
    while( nCase--)
    {
        memset(d, 0, sizeof(d));
        memset(vis, 0, sizeof(vis));
        string name;
        cin >> name;
        cin >> r >> c;
        for(i = 0; i < r; i++)
        {
            for(j = 0; j < c; j++)
            {
                cin >> a[i][j];
            }
        }
        nMax = d[0][0];
        for(i = 0; i < r; i++)
        {
            for(j = 0; j < c; j++)
            {
                nMax = max(nMax, dp(i, j));
            }
        }
        cout << name << ": "<< nMax << endl;
    }
    return 0;
}

int dp(int x, int y)
{
    if(vis[x][y])
    {
        return d[x][y];
    }
    vis[x][y] = 1;
    int nx, ny, i, nMax;
    nMax = 0;
    for(i = 0; i < 4; i++)
    {
        nx = x +dx[i];
        ny = y +dy[i];
        if(nx >= 0 && nx < r && ny >= 0 && ny < c
           && a[x][y]>a[nx][ny])
        {
            nMax = max(nMax, dp(nx, ny));
        }
    }
    d[x][y] = nMax+1;
    return d[x][y];
}
