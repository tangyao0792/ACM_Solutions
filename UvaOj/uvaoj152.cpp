#include<iostream>
#include<cmath>

    #include<cstdio>


#define N 5010

using namespace std;

typedef struct
{
    int x, y, z;
}Point;

Point p[N];
int dis[10];

void solve(int cnt);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int x, y, z, nCount, i;
    nCount = 0;
    while(cin >> x >> y >> z)
    {
        if(x == 0 && y == 0 && z == 0)
        {
            break;
        }
        p[nCount].x = x;
        p[nCount].y = y;
        p[nCount].z = z;
        nCount++;
    }

    solve( nCount);

    for(i = 0; i < 10; i++)
    {
        printf("%4d", dis[i]);
    }
    printf("\n");


    return 0;
}

void solve(int cnt)
{
    int i, j, nMin, d;
    int x, y, z;
    for(i = 0; i < 10; i++)
    {
        dis[i] = 0;
    }
    for(i = 0; i < cnt; i++)
    {
        nMin = 99999999;
        for(j = 0; j < cnt; j++)
        {
            if( j != i)
            {
                x = p[i].x - p[j].x;
                y = p[i].y - p[j].y;
                z = p[i].z - p[j].z;
                d = (int)(sqrt(x*x + y*y + z*z));
                if(d < nMin)
                {
                    nMin = d;
                }
            }
        }
        if(nMin < 10)
        {
            dis[nMin]++;
        }
    }
}
