#include<cstdio>
#include<cstring>
#include<iostream>
#include<vector>

using namespace std;

const int MAXN=10100;

vector<int> adj[MAXN];

int dfn[MAXN],low[MAXN],vis[MAXN],num[MAXN];
int n,m,nIndex;

inline void init()
{
	for(int i=0;i<n;i++)
		adj[i].clear();
	memset(vis,0,sizeof(vis));
	memset(num,0,sizeof(num));
	memset(dfn,0,sizeof(dfn));
	nIndex=0;
}

void tarjan(int u,int r, int fa)
{
	dfn[u]=low[u]=++nIndex;
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
	vis[u]=2;
}

int solve()
{
	int cnt=0;
	for(int i=0;i<n;i++)
		if(!vis[i])
		{
		    cnt++;
			tarjan(i,i,-1);
		}
	int ans=0;
	for(int i=0;i<n;i++)
		ans=max(ans,num[i]);
	return ans+cnt;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while(scanf("%d %d",&n,&m)==2)
	{
		if(n==0 && m==0)
			break;
        if(m==0)
        {
            printf("%d\n",n-1);
            continue;
        }
		init();
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
