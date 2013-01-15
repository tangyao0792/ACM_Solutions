#include<cstdio>
#include<cstring>

#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)


const int MAXM=1111*2000;
const int MAXN=1111;

int first[MAXN],dfn[MAXN],low[MAXN],s[MAXN],sp;
int id[MAXN];
int ins[MAXN];
int next[MAXM],u[MAXM],v[MAXM];
int n,a,b,nIndex,nscc,cnt;
int dis[MAXN/2][2];
int sx1,sy1,sx2,sy2,d;
int backu[MAXM],backv[MAXN],m;

inline int ABS(int x)
{
	return x>0?x:-x;
}

inline int getdis(int ax,int ay,int bx,int by)
{
	return ABS(ax-bx)+ABS(ay-by);
}

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
	cnt=0;
	memset(first,-1,sizeof(first));
}

inline void addback(int x,int y)
{
	backu[m]=x;
	backv[m++]=y;
}

inline void addedge(int x,int y)
{
	u[cnt]=x;
	v[cnt]=y;
	next[cnt]=first[x];
	first[x]=cnt++;
}

int solve(int lim)
{
	init();
	for(int i=0;i<m;i++)
		addedge(backu[i],backv[i]);

	for(int i=0;i<n;i++)
		for(int a=0;a<2;a++)
			for(int j=0;j<n;j++)
				for(int b=0;b<2;b++)
				{
					if(i==j)	continue;
					int tmp=0;
					if(a!=b)	tmp=d;
					tmp+=dis[i][a]+dis[j][b];
					if(tmp>lim)
						addedge(2*i+a,2*j+(b^1));
				}

	nscc=nIndex=sp=0;
	memset(dfn,0,sizeof(dfn));
	memset(ins,0,sizeof(ins));
	memset(id,0,sizeof(id));
	for(int i=0;i<2*n;i++)
		if(!dfn[i])
			if(!tarjan(i))
				return false;
	return true;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while(scanf("%d %d %d",&n,&a,&b)==3)
	{
		scanf("%d %d %d %d",&sx1,&sy1,&sx2,&sy2);
		m=0;
		int x,y;
		d=getdis(sx1,sy1,sx2,sy2);
		int r=0;
		for(int i=0;i<n;i++)
		{
			scanf("%d %d",&x,&y);
			dis[i][0]=getdis(sx1,sy1,x,y);
			r=max(r,dis[i][0]);

			dis[i][1]=getdis(sx2,sy2,x,y);
			r=max(r,dis[i][1]);
		}
		for(int i=0;i<a;i++)
		{
			scanf("%d %d",&x,&y);
			x--,y--;
			addback(2*x,2*y+1);
			addback(2*x+1,2*y);
			addback(2*y,2*x+1);
			addback(2*y+1,2*x);
		}

		for(int i=0;i<b;i++)
		{
			scanf("%d %d",&x,&y);
			x--,y--;
			addback(2*x,2*y);
			addback(2*x+1,2*y+1);
			addback(2*y,2*x);
			addback(2*y+1,2*x+1);
		}
		r*=2;
		r+=d;
		int l=0;
		int ans=-1;
		while(l<=r)
		{
			int mid=(l+r)/2;
			if(solve(mid))
			{
				r=mid-1;
				ans=mid;
			}
			else
				l=mid+1;
		}
		printf("%d\n",ans);
	}
	return 0;
}
