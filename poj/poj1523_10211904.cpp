#include<cstdio>
#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

const int MAXN=1001;

vector<int> adj[MAXN];
int dfn[MAXN],low[MAXN],vis[MAXN],num[MAXN];
int n,m,nIndex;

void tarjan(int u,int r, int fa)
{
    dfn[u]=low[u]=nIndex++;
    vis[u]=1;
    int t=adj[u].size();
    int son=0;
    for(int i=0;i<t;i++)
    {
        int v=adj[u][i];
        if(v==fa)   continue;

        if(vis[v]==0)
        {
            son++;
            tarjan(v,r,u);
            low[u]=min(low[u],low[v]);
            if((u==r && son>1) || (dfn[u]<=low[v] && u!=r))
            {
                num[u]++;
            }
        }
        else if(vis[v]==1)
            low[u]=min(low[u],dfn[v]);
    }
   // vis[u]=2;
}

void solve()
{
    memset(vis,0,sizeof(vis));
    memset(num,0,sizeof(num));
    nIndex=1;

    int cnt=0;
    for(int i=1;i<=n;i++)
        if(!vis[i])
        {
            cnt++;
            tarjan(i,i,-1);
        }
    int f=0;
    for(int i=1;i<=n;i++)
        if(num[i]>0)
        {
            f++;
            printf("  SPF node %d leaves %d subnets\n",i,num[i]+cnt);
        }
    if(!f)
        printf("  No SPF nodes\n");
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase=0;
    while(true)
    {
        if(nCase)   printf("\n");
        for(int i=0;i<MAXN;i++)
            adj[i].clear();

        nCase++;
        int x,y;
        n=0;
        m=0;
        while(scanf("%d",&x)==1 && x)
        {
            m++;
            scanf("%d",&y);
            n=max(n,max(x,y));
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        if(m==0)    break;
        printf("Network #%d\n",nCase);
        solve();

    }
    return 0;
}
