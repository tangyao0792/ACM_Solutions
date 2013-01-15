#include<cstdio>
#include<cstring>

#define min(a,b) ((a)>(b)?(b):(a))

const int MAXM=200*160;
const int MAXN=200;

int first[MAXN],dfn[MAXN],low[MAXN],s[MAXN],sp;
int id[MAXN];
int ins[MAXN];
int next[MAXM],u[MAXM],v[MAXM];
int n,m,nIndex,nscc,cnt;
int g[MAXN][MAXN];
int ind[MAXN],topo[MAXN],pt;
int col[MAXN];
int ans[MAXN];

int nf[MAXN],nn[MAXM],nu[MAXM],nv[MAXM],ncnt;

bool tarjan(int x)
{
	dfn[x]=low[x]=++nIndex;
	s[sp++]=x;
	ins[x]=1;
	for(int e=first[x];e!=-1;e=next[e])
	{
		int y=v[e];
		if(!dfn[y])
		{
			if(!tarjan(y))
				return false;
            low[x]=min(low[x],low[y]);
		}
		else if(ins[y])
		{
		    low[x]=min(low[x],dfn[y]);
		}
	}
	if(dfn[x]==low[x])
	{
		nscc++;
		int t;
		do
		{
			t=s[--sp];
			id[t]=nscc;
			ins[t]=0;
			if(id[t^1] && id[t^1]==id[t])
				return false;
		}while(t!=x);
	}
	return true;
}

inline void init()
{
	memset(ans,-1,sizeof(ans));
	cnt=0;
	memset(first,-1,sizeof(first));
	memset(dfn,0,sizeof(dfn));
	memset(id,0,sizeof(id));
	nIndex=sp=nscc=0;

	ncnt=0;
	memset(nf,-1,sizeof(nf));
	memset(g,0,sizeof(g));
	memset(ind,0,sizeof(ind));
	memset(col,0,sizeof(col));
	memset(ins,0,sizeof(ins));
}

inline void addedge(int x,int y)
{
//    printf("%d  ->  %d\n",x,y);
	u[cnt]=x;
	v[cnt]=y;
	next[cnt]=first[x];
	first[x]=cnt++;
}

inline void addnewedge(int x,int y)
{
//    printf("%d  ->  %d\n",x,y);
	nu[ncnt]=x;
	nv[ncnt]=y;
	nn[ncnt]=nf[x];
	nf[x]=ncnt++;
}

void topsort()
{
	sp=0;		// reuse the stack...
	pt=0;
	for(int i=1;i<=nscc;i++)
		if(ind[i]==0)
			s[sp++]=i;

	while(sp)
	{
		int u=s[--sp];
		topo[pt++]=u;
		for(int e=nf[u];e!=-1;e=nn[e])
		{
			int y=nv[e];
			ind[y]--;
			if(ind[y]==0)
				s[sp++]=y;
		}
	}
}

void color(int u)
{
	if(col[u])	return;
	col[u]=-1;
	for(int e=nf[u];e!=-1;e=nn[e])
	{
		color(nv[e]);
	}
}

void solve()
{
	bool flag=true;
	for(int i=0;i<4*n;i++)
		if(!dfn[i])
		{
			if(!tarjan(i))
			{
				flag=false;
				break;
			}
		}
	if(flag)
	{
		for(int i=0;i<4*n;i++)		//make new graph
		{
			for(int e=first[i];e!=-1;e=next[e])
			{
				int y=v[e];
				if(id[i]!=id[y])
				{
					if(g[id[y]][id[i]]==0)
					{
						ind[id[i]]++;
						addnewedge(id[y],id[i]);
						g[id[y]][id[i]]=1;
					}
				}
			}
		}

		topsort();

		for(int i=0;i<pt;i++)
		{
			int u=topo[i];
			if(col[u])	continue;
			col[u]=1;

			for(int j=0;j<4*n;j++)
			{
				if(id[j]==u)
					color(id[j^1]);
			}
		}

		for(int i=0;i<4*n;i++)
		{
			if(col[id[i]]==1)
			{
			    if(i%2)
                    ans[i/2]=-1;
                else
                    ans[i/2]=1;
			}
		}
		for(int i=1;i<n;i++)
		{
			if(i-1)	printf(" ");
			if(ans[i]==ans[0])
				printf("%dw",i);
			else
				printf("%dh",i);
		}
		puts("");
	}
	else
	{
		puts("bad luck");
	}
}
inline int get(char *str)
{
	int l=strlen(str);
	int offset=0;
	if(str[l-1]=='h')
		offset=n;
	int ans=0;
	for(int i=0;i<l-1;i++)
	{
		ans=ans*10+(str[i]-'0');
	}
	return ans+offset;

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
        init();
		addedge(2*0+1,2*0);
		addedge(2*n,2*n+1);
		for(int i=1;i<n;i++)
		{
			addedge(2*i,2*(i+n)+1);
			addedge(2*i+1,2*(i+n));

			addedge(2*(i+n),2*i+1);
			addedge(2*(i+n)+1,2*i);
		}
		char str[10];
		for(int i=0;i<m;i++)
		{
			scanf("%s",str);
			int x=get(str);

			scanf("%s",str);
			int y=get(str);

			addedge(2*x+1,2*y);
			addedge(2*y+1,2*x);
		}
		solve();
    }
    return 0;
}
