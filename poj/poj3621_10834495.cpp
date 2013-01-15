#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>

using namespace std;

const double eps=1e-3;
const int MAXN=1010;
const int MAXM=5010;
const int INF=1<<29;

int first[MAXN],val[MAXN];
int u[MAXM],v[MAXM],next[MAXM],a[MAXM],b[MAXM];
double w[MAXM];
int cnt;
int inn[MAXN];
double d[MAXN];
bool inq[MAXN];

int n,m;

inline void init()
{
	cnt=0;
	memset(first,-1,sizeof(first));
}

inline void addedge(int x,int y,int c,int d)
{
	u[cnt]=x;v[cnt]=y;
	a[cnt]=c;b[cnt]=d;

	next[cnt]=first[x];
	first[x]=cnt++;
}
inline double ABS(double x)
{
	return x<0?(-x):x;
}

bool spfa()
{
	queue<int> q;
	for(int i=2;i<=n;i++)
	{
		d[i]=INF;
	}
	d[1]=0;
	q.push(1);
	memset(inq,0,sizeof(inq));
	memset(inn,0,sizeof(inn));
	inq[1]=true;
	inn[1]=1;
	while(!q.empty())
	{
		int x=q.front();
		inq[x]=false;
		q.pop();

		for(int e=first[x];e!=-1;e=next[e])
		{
			int y=v[e];
			if(d[y]>d[x]+w[e])
			{
				d[y]=d[x]+w[e];
				if(!inq[y])
				{
					inq[y]=true;
					inn[y]++;
					if(inn[y]>n)
						return true;
					q.push(y);
				}
			}
		}

	}
	return false;
}

double solve()
{
//	double l=-INF/2;
//	double r=INF/2;
    double l=0;
    double r=1111;

	double ans=-1;

	while(ABS(l-r)>eps)
	{
		double mid=(l+r)/2;
		for(int i=0;i<cnt;i++)
		{
			w[i]=double(a[i])-mid*b[i];
			w[i]=-w[i];
//			w[i]=-w[i];
//			printf("%.2f    ",w[i]);
		}
//		puts("*");

		if(spfa())
		{
			ans=mid;
			l=mid;
		}
		else
		{
			r=mid;
		}
	}
	return ans;

}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in","r",stdin);
#endif
	while(scanf("%d %d",&n,&m)==2)
	{
		for(int i=1;i<=n;i++)
			scanf("%d",&val[i]);

        init();

		for(int i=0;i<m;i++)
		{
			int x,y,z;
			scanf("%d %d %d",&x,&y,&z);
			addedge(x,y,val[x],z);
		}

		double ans=solve();
		if(ans==-1)
		{
			printf("0\n");
		}
		else
		{
			printf("%.2f\n",ans);
		}

	}
	return 0;
}
