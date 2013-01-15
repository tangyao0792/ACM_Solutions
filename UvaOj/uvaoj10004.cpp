#include<iostream>
#include<cstring>
#define MAX 210

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif
using namespace std;

int vis[MAX];
int edge[MAX][MAX];
int nFlag;
int n,l;

void dfs(int x, int y, int v);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r", stdin);
#endif
    int i, x, y;
    while(cin >> n)
    {
       if(n == 0)
       {
           break;
       }
       memset(vis, 0, sizeof(int) * MAX);
       memset(edge, 0, sizeof(int) * MAX * MAX);
       cin >> l;
       for(i = 0; i < l; i++)
       {
           cin >> x >> y;
           edge[x][y] = 1;
       }
       nFlag = 0;
       dfs(x, y, 1);
       if(nFlag == -1)
       {
           cout << "NOT BICOLORABLE." << endl;
       }
       else
       {
           cout << "BICOLORABLE." << endl;
       }
    }
    return 0;
}

void dfs(int x, int y, int v)
{
    if(nFlag != 0)
    {
        return;
    }
    if(vis[y] != 0)
    {
        if(vis[y] == v)
        {
            return;
        }
        else
        {
            nFlag = -1;
            return;
        }
    }
    vis[y] = v;
    int i;
    for(i = 0; i < n; i++)
    {
        if(edge[y][i] == 1)
        {
            dfs(y, i, -v);
        }
    }
}
