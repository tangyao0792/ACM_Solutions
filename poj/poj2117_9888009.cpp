#include<cstdio>
#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

const int MAXN=10001;

vector<int> adj[MAXN];
int dfn[MAXN],low[MAXN],vis[MAXN],num[MAXN];
//vis[i]==1 means i is in stack
//vis[i]==2 means i is finished

int n,m,nIndex;

void tarjan(int u, int r, int fa)
{
    dfn[u]=low[u]=nIndex++;
    vis[u]=1;
    int t=adj[u].size();
    int son=0;
    for(int i=0;i<t;i++)
    {
        int v=adj[u][i];
        if( v ==fa) continue;
        if(vis[v]==0)
        {
            tarjan(v, r, u);
            low[u]=min(low[u],low[v]);
            son++;
            if((r==u && son>1) || (r!=u && dfn[u]<=low[v]))
                num[u]++;
        }
        else if (vis[v]==1)
        {
            low[u]=min(low[u],dfn[v]);
        }
    }
    vis[u]=2;
}

int solve()
{
    memset(vis,0,sizeof(vis));
    memset(num,0,sizeof(num));
    nIndex=1;
    int cnt=0;
    for(int i=0;i<n;i++)
        if(!vis[i])
        {
            cnt++;          //undirected graph's nscc
            tarjan(i, i, -1);
           // num[i]++;
        }

    int nMax=0;
    for(int i=0;i<n;i++)
        nMax=max(nMax,num[i]);
    return nMax+cnt;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d %d",&n,&m)==2 && !(!n && !m))
    {
        if(m==0)
        {
            printf("%d\n",n-1);
            continue;
        }
        for(int i=0;i<n;i++)
        {
            adj[i].clear();
            vis[i]=0;
        }
        for(int i=0;i<m;i++)
        {
            int x,y;
            scanf("%d %d",&x,&y);
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        printf("%d\n",solve());
    }
    return 0;
}
