#include<cstdio>
#include<cstring>
#include <math.h>
#include<iostream>
#include<algorithm>

using namespace std;

#define eps 1e-8
#define zero(x) (((x)>0?(x):-(x))<eps)
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

const int MAXN=55;
const int times=1000;
const int MAXL=30*50*times+100;
const double two=sqrt(2.0);

int r[MAXN];

double s[MAXN];
double b[MAXN];
int flag[MAXL];
bool visible[MAXN];

int n;

double getpos(int p)
{
	double ans=0;
	for(int i=0;i<p;i++)
	{
		double tmp=min(s[i],s[p]);
		ans=max(ans,b[i]+tmp*two);
	}
	return ans;
}

bool comp(int a,int b)
{
	return s[a]>s[b];
}

void paint(int i)
{
	int l=int((b[i]-s[i]/two)*times);
	int r=int((b[i]+s[i]/two)*times);
	for(int j=l;j<=r;j++)
	{
		if(flag[j]==-1)
		{
			flag[j]=i;
		}
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while(scanf("%d",&n)==1 && n)
	{
		for(int i=0;i<n;i++)
		{
			scanf("%lf",&s[i]);
			r[i]=i;
		}

		b[0]=s[0]/two;
		double right=0;
		for(int i=1;i<n;i++)
		{
			b[i]=getpos(i);
			right=max(right,b[i]+s[i]/two);
		}
		memset(flag,-1,sizeof(flag));
		memset(visible,0,sizeof(visible));

		sort(r,r+n,comp);
		for(int i=0;i<n;i++)
		{
			paint(r[i]);
		}
		int maxr=int(right*times);
		for(int i=0;i<=maxr;i++)
		{
			if(flag[i]!=-1)
			{
				visible[flag[i]]=true;
			}
		}
		int cnt=0;
		for(int i=0;i<n;i++)
		{
			if(visible[i])
			{
				if(cnt)
					printf(" ");
				cnt++;
				printf("%d",i+1);
			}
		}
		printf("\n");
	}
	return 0;
}
