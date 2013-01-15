#include<cstdio>
#define max(a,b) (a>b?a:b)

const int MAXN=50100;

int n;
int w[MAXN],h[MAXN];
int left[MAXN],right[MAXN];
int stk[MAXN][2],sp;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while(scanf("%d",&n)==1 && n!=-1)
	{
		for(int i=0;i<n;i++)
			scanf("%d %d",&w[i],&h[i]);

		sp=0;
		for(int i=0;i<n;i++)
		{
			left[i]=w[i];
			while(sp && stk[sp-1][0]>=h[i])
			{
				sp--;
				left[i]+=stk[sp][1];
			}
			stk[sp][0]=h[i];
			stk[sp++][1]=left[i];
		}
		sp=0;
		for(int i=n-1;i>=0;i--)
		{
			right[i]=w[i];
			while(sp && stk[sp-1][0]>=h[i])
			{
				sp--;
				right[i]+=stk[sp][1];
			}
			stk[sp][0]=h[i];
			stk[sp++][1]=right[i];
		}
		int ans=0;
		int s;
		for(int i=0;i<n;i++)
		{
			s=h[i]*(left[i]+right[i]-w[i]);
			ans=max(s,ans);
		}
		printf("%d\n",ans);
	}
	return 0;
}
