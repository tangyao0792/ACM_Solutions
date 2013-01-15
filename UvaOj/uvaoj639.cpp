#include<iostream>

#ifndef ONLINE_JUDGE
    #include<stdio.h>
#endif

using namespace std;

char chess[4][4];
int n;
int nMax;

void dfs(int cur);
int check();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif

    int i, j;
    while( cin >> n)
    {
        if(n == 0)
        {
            break;
        }
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < n; j++)
            {
                cin >> chess[i][j];
            }
        }
        nMax = 0;
        dfs(0);
        cout << nMax << endl;
    }
    return 0;
}
int check()
{
    int i , j;
    int nFlagX = 1;
    int nFlagY = 1;
    for(i = 0; i < n; i++)
    {
        nFlagX = 1;
        nFlagY = 1;
        for(j = 0; j < n; j++)
        {
            if(chess[i][j] == 'o')
            {
                if(nFlagX == 0)
                {
                    return 0;
                }
                nFlagX = 0;
            }
            else if(chess[i][j] == 'X')
            {
                nFlagX = 1;
            }

            if(chess[j][i] == 'o')
            {
                if(nFlagY == 0)
                {
                    return 0;
                }
                nFlagY = 0;
            }
            else if(chess[j][i] == 'X')
            {
                nFlagY = 1;
            }
        }
    }


    return 1;
}
void dfs(int cur)
{
    if(cur > n * n-1)
    {
        if(check() == 1)
        {
            int temp = 0;
            for(int i = 0; i < n; i++)
            {
                for(int j = 0; j < n; j++)
                {
                    if(chess[i][j] == 'o')
                    {
                        temp++;
                    }
                }
            }
            if(temp > nMax)
            {
                nMax = temp;
            }
        }
        return;
    }
    int nx, ny;
    nx = cur / n;
    ny = cur % n;

    if(chess[nx][ny] != 'X')
    {
        chess[nx][ny] = '.';
        dfs(cur+1);
        chess[nx][ny] = 'o';
        dfs(cur+1);
    }
    else
    {
        dfs(cur+1);
    }
}
