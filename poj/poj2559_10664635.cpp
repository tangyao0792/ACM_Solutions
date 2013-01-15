#include<cstdio>
#include<cstring>

#define max(a,b) (a>b?a:b)

typedef long long LL;

const int MAXN=100100;

LL stk[MAXN][2],a[MAXN];
int left[MAXN],right[MAXN];
int sp,n;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while(scanf("%d",&n)==1 && n)
	{
		sp=0;
		LL ans=0;
		for(int i=0;i<n;i++)
		{
			scanf("%lld",&a[i]);
		}
		sp=0;
		for(int i=0;i<n;i++)
		{
		    left[i]=1;
		    while(sp && stk[sp-1][0]>=a[i])
		    {
		        sp--;
		        left[i]+=stk[sp][1];
		    }
		    stk[sp][0]=a[i];
		    stk[sp++][1]=left[i];
		}
        sp=0;
		for(int i=n-1;i>=0;i--)
		{
		    right[i]=1;
		    while(sp && stk[sp-1][0]>=a[i])
		    {
		        sp--;
		        right[i]+=stk[sp][1];
		    }
		    stk[sp][0]=a[i];
		    stk[sp++][1]=right[i];
		}
		LL s=0;
		for(int i=0;i<n;i++)
		{
		    s=a[i]*(left[i]+right[i]-1);
		    ans=max(ans,s);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
