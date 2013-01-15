#include<cstdio>
#include<cstring>
#define min(a,b) (a<b?a:b)

const int MAXN=2200;
const int MAXM=2200*2200;

int low[MAXN],dfn[MAXN],ins[MAXN],s[MAXN],id[MAXN];
int nscc,nIndex,sp;

int u[MAXM],v[MAXM],next[MAXM];
int first[MAXN],cnt;

int g[MAXN][MAXN];

int n,m;

inline void addedge(int x,int y)
{
    if(g[x][y]) return;
    g[x][y]=1;
	u[cnt]=x;v[cnt]=y;
	next[cnt]=first[x];
	first[x]=cnt++;
}

bool tarjan(int u)
{
	dfn[u]=low[u]=nIndex++;
	s[sp++]=u;
	ins[u]=1;

	for(int e=first[u];e!=-1;e=next[e])
	{
		int y=v[e];

		if(!ins[y])
		{
			if(!tarjan(y))
				return false;
			low[u]=min(low[u],low[y]);
		}
		else
		{
			low[u]=min(low[u],dfn[y]);
		}
	}

	if(dfn[u]==low[u])
	{
		nscc++;
		while(1)
		{
			int t=s[--sp];
			ins[t]=0;
			id[t]=nscc;
			if(id[t]==id[t^1])
				return false;
			if(t==u)
				break;
		}
	}
	return true;
}

bool solve()
{
	memset(dfn,0,sizeof(dfn));
	memset(ins,0,sizeof(ins));
	memset(id,0,sizeof(id));
	sp=0;
	nscc=0;
	nIndex=1;

	for(int i=0;i<2*n;i++)
	{
		if(!dfn[i])
		{
			if(!tarjan(i))
				return false;
		}
	}
	return true;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while(scanf("%d %d",&n,&m)==2)
	{
	    for(int i=0;i<2*n;i++)
            for(int j=0;j<2*n;j++)
                g[i][j]=0;

        for(int i=0;i<2*n;i++)
            first[i]=-1;

		cnt=0;

		for(int i=0;i<m;i++)
		{
			int a,b,c;
			char s[22];
			scanf("%d %d %d %s",&a,&b,&c,s);
			if(c==0)
			{
				if(s[0]=='A')
				{
					addedge(2*a+1,2*b);
					addedge(2*b+1,2*a);
				}
				else if(s[0]=='O')
				{
					addedge(2*a+1,2*a);
					addedge(2*b+1,2*b);
				}
				else
				{
					addedge(2*a+1,2*b+1);
					addedge(2*b+1,2*a+1);
					addedge(2*a,2*b);
					addedge(2*b,2*a);
				}
			}
			else
			{
				if(s[0]=='A')
				{
					addedge(2*a,2*a+1);
					addedge(2*b,2*b+1);
				}
				else if(s[0]=='O')
				{
					addedge(2*a,2*b+1);
					addedge(2*b,2*a+1);
				}
				else
				{
					addedge(2*a+1,2*b);
					addedge(2*b+1,2*a);
					addedge(2*a,2*b+1);
					addedge(2*b,2*a+1);
				}
			}
		}
		if(solve())
			puts("YES");
		else
			puts("NO");
	}
	return 0;
}
