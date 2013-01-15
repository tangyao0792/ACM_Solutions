#include<cstdio>
#include<cstring>

#define min(a,b) (a>b?b:a)
#define max(a,b) (a>b?a:b)


const int MAXN= 10100;
const int MAXM= 50100;

int n,m;

int first[MAXN],dfn[MAXN],low[MAXN],s[MAXN],sp,ins[MAXN],nscc,nIndex,id[MAXN];
int u[MAXM],v[MAXM],next[MAXM],cnt;
int num[MAXM];

inline void add(int x,int y)
{
	u[cnt]=x;
	v[cnt]=y;
	next[cnt]=first[x];
	first[x]=cnt++;
}

inline void init()
{
	cnt=0;
	memset(first,-1,sizeof(first));
	memset(id,0,sizeof(id));
	memset(dfn,0,sizeof(dfn));
	memset(ins,0,sizeof(ins));
	memset(num,0,sizeof(num));
	sp=0;
	nscc=nIndex=0;
}

void tarjan(int u)
{
	dfn[u]=low[u]=++nIndex;
	s[sp++]=u;
	ins[u]=1;

	for(int e=first[u];e!=-1;e=next[e])
	{
		int y=v[e];
		if(!dfn[y])
		{
			tarjan(y);
			low[u]=min(low[u],low[y]);
		}
		else if(ins[y])
			low[u]=min(low[u],dfn[y]);
	}
	if(low[u]==dfn[u])
	{
		int t;
		nscc++;
		do
		{
			t=s[--sp];
			id[t]=nscc;
			num[id[t]]++;
			ins[t]=0;
		}while(t!=u);
	}
}

int outd[MAXN];

int solve()
{
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			tarjan(i);

	for(int i=1;i<=n;i++)
		for(int e=first[i];e!=-1;e=next[e])
		{
			int j=v[e];
			if(id[i]!=id[j])
			{
				outd[id[i]]++;
			}
		}
	int cnt=0;
	int p=1;
	for(int i=1;i<=nscc;i++)
		if(outd[i]==0)
		{
			cnt++;
			p=i;
		}
	if(cnt>1)
		return 0;
	return num[p];
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
