#include<cstdio>
#include<cstring>
#include<cmath>
#include<iostream>

using namespace std;

const int MAXN=1010;
const double eps=1e-5;
const long long INF=1ll<<60;

int x[MAXN],y[MAXN],z[MAXN];
int n;
double a[MAXN][MAXN],b[MAXN][MAXN],d[MAXN][MAXN];
int vis[MAXN];
//#define ABS(x) ((x)<0?(-x):(x))

inline double ABS(double x)
{
    return x<0?-x:x;
}

double lowcost[MAXN];
int closet[MAXN];
double prim()
{
	int i,j,minone;
	double mindis;
	double p=0,q=0;
	for(i = 1;i < n;i++)
	{
		lowcost[i] = d[0][i];
		closet[i]=0;
	}
	memset(vis,0,sizeof(vis));
	vis[0]=1;
	for(i = 0;i < n-1;i++)
	{
		mindis = INF;
		for(j = 0;j < n;j++)
			if(!vis[j] && mindis > lowcost[j])
			{
				mindis = lowcost[j];
				minone = j;
			}
        p+=a[minone][closet[minone]];
        q+=b[minone][closet[minone]];

		vis[minone]=1;

		for(j = 0;j < n;j++)
			if(!vis[j] && d[j][minone] < lowcost[j])
			{
				lowcost[j] = d[j][minone];
				closet[j]=minone;
			}
	}
	return p/q;
}

double dinkelback()
{
	double l,ans;
	l=0;
	while(true)
	{
		ans=l;
		for(int i=0;i<n;i++)
		{
			for(int j=i+1;j<n;j++)
			{
				d[i][j]=d[j][i]=a[i][j]-l*b[i][j];
			}
		}

		l=prim();
		if(ABS(l-ans)<eps)
			break;
	}
	return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in","r",stdin);
#endif
	while(scanf("%d",&n)==1 && n)
	{
		for(int i=0;i<n;i++)
			scanf("%d %d %d",&x[i],&y[i],&z[i]);

		for(int i=0;i<n;i++)
			for(int j=i+1;j<n;j++)
			{
				int ta=x[i]-x[j];
				int tb=y[i]-y[j];
				a[i][j]=a[j][i]=ABS(z[i]-z[j]);
				b[i][j]=b[j][i]=sqrt(double(ta*ta+tb*tb));
			}
		printf("%.3f\n",dinkelback());
	}
	return 0;
}
