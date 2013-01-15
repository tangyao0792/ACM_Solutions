#include<cstdio>
#include<cstring>

#define max(a,b) (a>b?a:b)

const int N = 20020;
const int MAXN=1000001;
int s[N];                          // N > 256
int n,k, sa[N], height[N], rank[N], tmp[MAXN], top[MAXN];

void makesa()
{                       // O(N * log N)
	int i, j, len, na;
	na = (n < MAXN? MAXN: n);
	memset(top, 0, na * sizeof(int));
	for (i = 0; i < n ; i++)
		top[ rank[i] = s[i] & 0xff ]++;
	for (i = 1; i < na; i++)
		top[i] += top[i - 1];
	for (i = 0; i < n ; i++)
		sa[ --top[ rank[i] ] ] = i;
	for (len = 1; len < n; len <<= 1)
	{
		for (i = 0; i < n; i++)
		{
			j = sa[i] - len;
			if (j < 0) j += n;
			tmp[ top[ rank[j] ]++ ] = j;
		}
		sa[ tmp[ top[0] = 0 ] ] = j = 0;
		for (i = 1; i < n; i++)
		{
			if (rank[ tmp[i] ] != rank[ tmp[i-1] ] ||
				rank[ tmp[i]+len ]!=rank[ tmp[i-1]+len ])
				top[++j] = i;
			sa[ tmp[i] ] = j;
		}
		memcpy(rank, sa , n * sizeof(int));
		memcpy(sa  , tmp, n * sizeof(int));
		if (j >= n - 1) break;
	}
}

void make_height()
{                        
	int i, j, k;
	for (j = rank[height[i=k=0]=0]; i < n - 1; i++, k++)	
	while (k >= 0 && s[i] != s[ sa[j-1] + k ])
		height[j] = (k--), j = rank[ sa[j] + 1 ];							
}

int solve()
{
	int l=1,r=n-1,mid,cnt,nMax;
	while(l<=r)
	{
		nMax=cnt=1;
		mid=(l+r)/2;
		for(int i=2;i<=n;i++)
		{
			if(height[i]<mid)
			{
				cnt=0;
			}
			cnt++;
			nMax=max(nMax,cnt);
		}
		if(nMax>=k)
			l=mid+1;
		else
			r=mid-1;
	}
	return r;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif

	while(scanf("%d %d",&n,&k)==2)
	{
		for(int i=0;i<n;i++)
			scanf("%d",&s[i]);
		n++;
		s[n-1]=0;
		makesa();
		make_height();

		int ans=solve();
		printf("%d\n",ans);
	}

	return 0;
}
