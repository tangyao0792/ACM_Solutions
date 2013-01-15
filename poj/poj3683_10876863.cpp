#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;

struct node
{
	int st,end,l;
}p[1111];

const int MAXM=1111*2000;
const int MAXN=2010;

int first[MAXN],dfn[MAXN],low[MAXN],s[MAXN],sp;
int id[MAXN];
int ins[MAXN];
int next[MAXM],u[MAXM],v[MAXM];
int n,nIndex,nscc,cnt;
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

inline void swap(int &a,int &b)
{
	int tmp=a;
	a=b;
	b=tmp;
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
	for(int i=0;i<2*n;i++)
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
		puts("YES");
		for(int i=0;i<2*n;i++)		//make new graph
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

			for(int j=0;j<2*n;j++)
			{
				if(id[j]==u)
					color(id[j^1]);
			}
		}

		for(int i=0;i<2*n;i++)
		{
			if(col[id[i]]==1)
			{
			    if(i%2)
                    ans[i/2]=-1;
                else
                    ans[i/2]=1;
			}
		}
		for(int i=0;i<n;i++)
		{
			if(ans[i]==1)
				printf("%02d:%02d %02d:%02d\n",p[i].st/60,p[i].st%60,(p[i].st+p[i].l)/60,(p[i].st+p[i].l)%60);
			else
				printf("%02d:%02d %02d:%02d\n",(p[i].end-p[i].l)/60,(p[i].end-p[i].l)%60,p[i].end/60,p[i].end%60);
		}
	}
	else
	{
		puts("NO");
	}

}
bool intersect(int ax,int ay,int bx,int by)
{
    ay--;by--;
	if(ax>ay)	swap(ax,ay);
	if(bx>by) 	swap(bx,by);

	if(bx<=ax && ax<=by)
		return true;
	if(bx<=ay && ay<=by)
		return true;
	if(ax<=bx && bx<=ay)
		return true;
	if(ax<=by && by<=ay)
		return true;

	return false;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while(scanf("%d",&n)==1)
	{
		init();
		for(int i=0;i<n;i++)
		{
			int h,m;
			scanf("%d:%d",&h,&m);
			p[i].st=h*60+m;

			scanf("%d:%d",&h,&m);
			p[i].end=h*60+m;

			scanf("%d",&p[i].l);
		}
		for(int i=0;i<n;i++)
		{
			for(int j=i+1;j<n;j++)
			{
			    int f02=0,f03=0,f12=0,f13=0;
				if(intersect(p[i].st,p[i].st+p[i].l,p[j].st,p[j].st+p[j].l))
				{
				    f02=1;
				}
				if(intersect(p[i].st,p[i].st+p[i].l,p[j].end-p[j].l,p[j].end))
				{
                    f03=1;
				}
				if(intersect(p[i].end-p[i].l,p[i].end,p[j].st,p[j].st+p[j].l))
				{
                    f12=1;
				}
				if(intersect(p[i].end-p[i].l,p[i].end,p[j].end-p[j].l,p[j].end))
				{
                    f13=1;
				}
				if(f02)
				{
                    addedge(i*2,j*2+1);
					addedge(j*2,i*2+1);
				}
                if(f03)
				{
                    addedge(i*2,j*2);
					addedge(j*2+1,i*2+1);
				}
                if(f12)
				{
                    addedge(i*2+1,j*2+1);
					addedge(j*2,i*2);
				}
                if(f13)
				{
                    addedge(i*2+1,j*2);
					addedge(j*2+1,i*2);
				}
			}
		}
		solve();
	}
	return 0;
}
