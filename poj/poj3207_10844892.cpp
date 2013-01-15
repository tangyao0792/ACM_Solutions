#include<cstdio>
#include<cstring>

#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)

const int MAXN=1011;
const int MAXM=505;

struct Line
{
	int x,y;
}l[MAXM];

int g[MAXM*2][MAXM*2];
int n,m;

inline bool intersect(int i,int j)
{
    if(l[i].x>l[j].y || l[j].x>l[i].y)
        return false;
    if(l[i].y>l[j].y && l[i].x<l[j].x)
        return false;
    if(l[j].y>l[i].y && l[j].x<l[i].x)
        return false;
    return true;
}

int dfn[MAXN],low[MAXN],s[MAXN],nscc,nIndex,sp;
int ins[MAXN];
int id[MAXN];

bool tarjan(int u)
{
	dfn[u]=low[u]=nIndex++;
	s[sp++]=u;
	ins[u]=1;

	for(int i=0;i<n;i++)
	{
		if(g[u][i])
		{
			if(!ins[i])
			{
				if(!tarjan(i))
					return false;
				low[u]=min(low[u],low[i]);
			}
			else
			{
				low[u]=min(low[u],dfn[i]);
			}
		}
	}
	if(dfn[u]==low[u])
	{
		nscc++;
		while(true)
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
	nIndex=1;
	nscc=0;
	sp=1;

	for(int i=0;i<n;i++)
		if(!dfn[i])
		{
			if(!tarjan(i))
				return false;
		}
	return true;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	scanf("%d %d",&n,&m);
	n=2*m;

	for(int i=0;i<m;i++)
	{
		int a,b;
		scanf("%d %d",&a,&b);
		l[i].x=min(a,b);
		l[i].y=max(a,b);
	}

	memset(g,0,sizeof(g));

	for(int i=0;i<m;i++)
	{
		for(int j=i+1;j<m;j++)
		{
			if(intersect(i,j))
			{
				g[i*2][j*2+1]=1;
				g[j*2][i*2+1]=1;
				g[i*2+1][j*2]=1;
				g[j*2+1][i*2]=1;
//				printf("%d  ->  %d\n",i*2,j*2+1);
//				printf("%d  ->  %d\n",j*2,i*2+1);
			}
		}
	}

	if(solve())
		puts("panda is telling the truth...");
	else
		puts("the evil panda is lying again");

	return 0;
}
