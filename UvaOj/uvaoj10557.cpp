#include<iostream>
#include<cstring>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

#define N 110

int room[N][N];
int vis[N];
int energy[N];
int curEnergy[N];

int nCase;

void firstDfs(int cur, int player);
int dfs(int cur, int player);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int i, j, doorWays, reachableRoom;
    while( cin >> nCase)
    {
        if(nCase == -1)
        {
            break;
        }
        memset( room, 0, sizeof(int) * N * N);
        memset( vis, 0, sizeof(int) * N);
        for(i = 1; i <= nCase; i++)
        {
            cin >> energy[i];
            cin >> doorWays;
            for(j = 0; j < doorWays; j++)
            {
                cin >> reachableRoom;
                room[i][reachableRoom] = 1;
            }
        }
        firstDfs(1, 100);
        memset( vis, 0, sizeof(int) * N);
        if(nCase == 1 || dfs(1, 100) == 1)
        {
            cout << "winnable" << endl;
        }
        else
        {
            cout << "hopeless" << endl;
        }
    }
    return 0;
}

int dfs(int cur, int player)
{
    if(cur == nCase)
    {
        return 1;
    }
    player += energy[cur];
    if(player < 1)
    {
        return 0;
    }
    int i;

    for(i = 1; i <= nCase; i++)
    {
        if(room[cur][i] == 1)
        {
            room[cur][i] = 0;
            if(dfs(i, player) == 1)
            {
                return 1;
            }
        }
    }
    return 0;
}

void firstDfs(int cur, int player)
{
    if(cur == nCase)
    {
        return;
    }
    if(vis[cur] > 1)
    {
        if(player > curEnergy[cur])
        {
            energy[cur] = 999999999;
        }
        return;
    }
    curEnergy[cur] = player;
    int i;
    for(i = 1; i <= nCase; i++)
    {
        if(room[cur][i] == 1)
        {
            vis[i]++;
            firstDfs(i, player+energy[i]);
        }
    }
}


