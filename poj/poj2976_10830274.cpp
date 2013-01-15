#include<cstdio>
#include<iostream>
#include<algorithm>

using namespace std;

const int MAXN=1020;
const double eps=1e-4;

int n,k;
typedef long long LL;
LL a[MAXN],b[MAXN];
double d[MAXN];
int r[MAXN];

bool cmp(int x,int y)
{
	return d[x]>d[y];
}
inline double abs(double x)
{
	return x<0?(-x):x;
}

double Dinkelback()
{
	double ans,l;
	l=30;
	while(true)
	{
		ans=l;
		for(int i=0;i<n;i++)
		{
			r[i]=i;
			d[i]=double(a[i])-l*b[i];
		}

		double p=0,q=0;
		sort(r,r+n,cmp);
		for(int i=0;i<n-k;i++)
		{
			p+=a[r[i]];
			q+=b[r[i]];
		}
		l=p/q;
		if(abs(ans-l)<eps)
			break;
	}
	return 100*ans;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in","r",stdin);
#endif
	while(scanf("%d %d",&n,&k)==2)
	{
		if(n==0 && k==0)
			break;
		for(int i=0;i<n;i++)
		{
			scanf("%lld",&a[i]);
		}
		for(int i=0;i<n;i++)
		{
			scanf("%lld",&b[i]);
		}
		printf("%.0f\n",Dinkelback());
	}
	return 0;
}
