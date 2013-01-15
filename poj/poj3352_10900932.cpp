#include<cstdio>
#include<cstring>

#define min(a,b) (a>b?b:a)
#define max(a,b) (a>b?a:b)

const int MAXN=1100;
const int MAXM=2*MAXN;

struct edge
{
	int next,id,v,u;
}e[MAXM];

int dfn[MAXN],low[MAXN],vis[MAXN],f[MAXN],out[MAXM],vise[MAXM],cnt;
int nIndex;
int n,m;

inline void init()
{
	memset(out,0,sizeof(out));
	memset(dfn,0,sizeof(dfn));
	memset(vis,0,sizeof(vis));
	memset(f,-1,sizeof(f));
	memset(vise,0,sizeof(vise));
	cnt=0;
}

inline void add(int x,int y)
{
	e[cnt].u=x;
	e[cnt].v=y;
	e[cnt].next=f[x];
	f[x]=cnt++;

	e[cnt].u=y;
	e[cnt].v=x;
	e[cnt].next=f[y];
	f[y]=cnt++;
}

void tarjan(int u)
{
	dfn[u]=low[u]=nIndex++;
	vis[u]=1;
	for(int i=f[u];i!=-1;i=e[i].next)
	{
		if(vise[i/2])   continue;
		vise[i/2]=1;
		int v=e[i].v;
		if(!vis[v])
		{
			tarjan(v);
		}
		low[u]=min(low[u],low[v]);
		if(dfn[u]<low[v])
		{
			out[i/2]=1;
		}
	}
	vis[u]=2;
}

int nf[MAXN],u[MAXN*2],v[MAXN*2],next[MAXN*2],ncnt;
int id[MAXN];
int ind[MAXN];

inline void addnew(int x,int y)
{
	u[ncnt]=x;
	v[ncnt]=y;
	next[ncnt]=nf[x];
	nf[x]=ncnt++;
}
int nscc;

void dfs(int x,int fa)
{
	id[x]=nscc;
	for(int i=nf[x];i!=-1;i=next[i])
	{
		int y=v[i];
		if(id[y])
			continue;
		dfs(y,x);
	}
}

int solve()
{
	for(int i=1;i<=n;i++)
		if(!vis[i])
			tarjan(i);

	ncnt=0;
	memset(nf,-1,sizeof(nf));
	memset(ind,0,sizeof(ind));

	for(int i=0;i<cnt;i++)
	{
		if(!out[i/2])
			addnew(e[i].u,e[i].v);
	}

	memset(id,0,sizeof(id));
	nscc=1;

	for(int i=1;i<=n;i++)
		if(!id[i])
		{
			dfs(i,-1);
			nscc++;
		}

	for(int i=0;i<cnt;i+=2)
	{
		if(out[i/2])
		{
			ind[id[e[i].u]]++;
			ind[id[e[i].v]]++;
		}
	}
	int ans=0;
	for(int i=1;i<nscc;i++)
		if(ind[i]==1)
			ans++;
	return (ans+1)/2;

}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif

	while(scanf("%d %d",&n,&m)==2)
	{
		init();
		for(int i=0;i<m;i++)
		{
			int x,y;
			scanf("%d %d",&x,&y);
			add(x,y);
		}
		printf("%d\n",solve());
	}

	return 0;
}
