#include<iostream>
#include<sstream>
#include<cstring>
#include<cmath>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

int n, k;
int t[10];                  //速度
int g[10][110];             //5个电梯，100层楼
int d[110];
int v[110];
int c[110];


const int INF = 1<<28;

void dijkstra();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    string line;
    while( getline(cin, line))
    {
        memset(g, 0, sizeof(g));
        memset(t, 0, sizeof(t));
        memset(v, 0, sizeof(v));
        memset(c, -1, sizeof(v));

        stringstream ss(line);

        ss >> n >> k;
        for(int i = 0; i < n; i++)
        {
            cin >> t[i];
        }
        getline(cin, line);
        for(int i = 0; i < n; i++)
        {
            getline(cin, line);
            stringstream ssf(line);
            int j;
            while(ssf >> j)
            {
                g[i][j] = 1;
            }
        }
        dijkstra();
        if(k == 0)
        {
            cout << 0 << endl;
        }
        else if(d[k] == INF)
        {
            cout << "IMPOSSIBLE" << endl;
        }
        else
        {
            cout << d[k]-60 << endl;
        }
    }
    return 0;
}

void dijkstra()
{
    for(int i = 1; i <= 100; i++)
    {
        d[i] = INF;
    }
    d[0] = 0;
    for(int i = 0; i <= 100; i++)
    {
        int x, m = INF;
        for(int y = 0; y <= 100; y++)
        {
            if(!v[y] && d[y] <= m)
            {
                m = d[x=y];
            }
        }
        v[x] = 1;
        for(int y = 0; y <= 100; y++)
        {
            for(int i = 0; i < n; i++)
            {
                if(g[i][y]&&g[i][x])
                {
                    int tmp = (c[x] == i ?:0,1);
                    if(d[y] > (d[x]+abs((double)x-y)*t[i]+tmp*60))          //假如能相等，取还是不取？
                    {
                        d[y] =(int)(d[x]+abs((double)x-y)*t[i]+tmp*60);
                        c[x] = i;
                    }
                }
            }
        }
    }
}
