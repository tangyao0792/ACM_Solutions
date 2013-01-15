#include<cstdio>
#include<cstring>
#include<cmath>

#define min(a,b) (a<b?a:b)

const int N = 20020;

int a[N];
char s[N];
// N > 256
int n, sa[N], height[N], rank[N], tmp[N], top[N];
void makesa()
{
// O(N * log N)
    int i, j, len, na;
    na = (n < 256 ? 256 : n);
    memset(top, 0, na * sizeof(int));

    for (i = 0; i < n ; i++) top[ rank[i] = s[i] & 0xff ]++;
    for (i = 1; i < na; i++) top[i] += top[i - 1];
    for (i = 0; i < n ; i++)
        sa[ --top[ rank[i] ] ] = i;
    for (len = 1; len < n; len <<= 1)
    {
        for (i = 0; i < n; i++)
        {
            j = sa[i] - len; if (j < 0) j += n;
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
        memcpy(sa , tmp, n * sizeof(int));
        if (j >= n - 1) break;
    }
}
void lcp(){
// O(4 * N)
int i, j, k;
    for (j = rank[height[i=k=0]=0]; i < n - 1; i++, k++)
        while (k >= 0 && s[i] != s[ sa[j-1] + k ])
            height[j] = (k--), j = rank[ sa[j] + 1 ];
}


int solve()
{
	int l,r,low,high,mid;
	bool flag;
	l=1;r=n/2+1;

    while(l<=r)
    {
        mid=(l+r)/2;
        flag=false;
        low=high=sa[1];
        for(int i=2;i<=n && !flag;i++)
        {
            if(height[i]<mid)
            {
                low=high=sa[i];
            }
            else
            {
                if(low>sa[i]) low=sa[i];
                if(high<sa[i])    high=sa[i];
                int len=high-low;
                if(len>=mid)
                {
                    flag=true;
                    break;
                }
            }


        }
        if(flag)
            l=mid+1;
        else
            r=mid-1;
    }

	return r>=4?r+1:0;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif

	while(scanf("%d",&n)==1 && n)
	{
		for(int i=0;i<n;i++)
			scanf("%d",&a[i]);
        if(n<10)
        {
            printf("0\n");
            continue;
        }
		for(int i=0;i<n-1;i++)
			s[i]=char(a[i+1]-a[i]+100);
        s[n-1]=0;
		makesa();
		lcp();

		int ans=solve();
		printf("%d\n",ans);
	}


	return 0;
}
