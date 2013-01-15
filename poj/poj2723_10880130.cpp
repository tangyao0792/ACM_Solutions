#include<cstdio>
#include<cstring>
#define min(a,b) (a<b?a:b)

const int MAXM=1111*2222;
const int MAXN=5050;

int first[MAXN],dfn[MAXN],low[MAXN],s[MAXN],sp,ins[MAXN];
int id[MAXN];
int next[MAXM],u[MAXM],v[MAXM];
int n,nIndex,nscc,cnt,m;

int rev[MAXN];
int lock[MAXN][2];

bool tarjan(int x,int lim)
{
	dfn[x]=low[x]=++nIndex;
	s[sp++]=x;
	ins[x]=1;
	for(int e=first[x];e!=-1;e=next[e])
	{

		int y=v[e];
		if(y>lim+1)	continue;
		if(!dfn[y])
		{

			if(!tarjan(y,lim))
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
	cnt=0;
	memset(first,-1,sizeof(first));
}

inline void addedge(int x,int y)
{
//	    printf("(%d,%d)  ->  (%d,%d) \n",x/2,x%2,y/2,y%2);
	u[cnt]=x;
	v[cnt]=y;
	next[cnt]=first[x];
	first[x]=cnt++;
//	if(cnt>MAXM)
//	while(1);
}

bool solve(int lim)
{
	memset(ins,0,sizeof(ins));
	memset(dfn,0,sizeof(dfn));
	memset(id,0,sizeof(id));
	nIndex=sp=nscc=0;

	for(int i=2;i<=2*m;i++)
		if(!dfn[i])
		{
			if(!tarjan(i,lim))
			{
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
		if(n==0 && m==0)
			break;
		init();
		for(int i=0;i<n;i++)
		{
			int x,y;
			scanf("%d %d",&x,&y);
			rev[x]=y;
			rev[y]=x;
		}
		for(int i=1;i<=m;i++)
		{
			scanf("%d %d",&lock[i][0],&lock[i][1]);
		}
		for(int i=1;i<=m;i++)
			for(int a=0;a<2;a++)
				for(int j=1;j<=m;j++)
				{
				    if(i==j)    continue;
					for(int b=0;b<2;b++)
					{
						if(rev[lock[i][a]]==lock[j][b])
						{
							addedge(2*i+a,2*j+(b^1));
						}
					}
				}

		int l=0,r=m;
		while(l<=r)
		{
			int mid=(l+r)/2;
			if(solve(mid*2))
				l=mid+1;
			else
				r=mid-1;
		}
		printf("%d\n",r);
	}
	return 0;
}
