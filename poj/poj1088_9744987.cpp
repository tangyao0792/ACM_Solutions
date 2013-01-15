#include<iostream>
#include<cstring>
#include<cstdio>

using namespace std;

int r, c;
int g[110][110];
int d[110][110];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

int dp(int x, int y);

int main()
{
   
    while(cin >>r >>c)
    {
        memset(d, 0, sizeof(d));
        memset(g, 0, sizeof(g));
        int i, j;
        for(i = 0; i < r; i++)
        {
            for(j = 0; j < c; j++)
            {
                cin >> g[i][j];
            }
        }
        for(i = 0; i < r; i++)
        {
            for(j = 0; j < c; j++)
            {
                d[i][j] = dp(i, j);
            }
        }
        int nMax = d[0][0];
        for(i = 0; i < r; i++)
        {
            for(j = 0; j < c; j++)
            {
                if(nMax < d[i][j])
                {
                    nMax = d[i][j];
                }
            }
        }
        cout << nMax+1 << endl;
    }
    return 0;
}

int dp(int x, int y)
{
    if(d[x][y])
    {
        return d[x][y];
    }
    int i, nMax = 0;
    for(i = 0; i < 4; i++)
    {
        int nx = x+dx[i];
        int ny = y+dy[i];
        if(nx < r && nx >= 0
           && ny < c && ny >= 0 && g[x][y] > g[nx][ny])
        {
            int temp = dp(nx, ny)+1;
            if( nMax < temp)
            {
                nMax = temp;
            }
        }
    }
    d[x][y] = nMax;
    return d[x][y];
}
