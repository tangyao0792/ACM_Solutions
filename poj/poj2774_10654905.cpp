#include<cstdio>
#include<cstring>
#include<cmath>

#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)

const int N=200200;

//INIT: n = strlen(s) + 1;
//CALL: makesa(); lcp();SparseTable();get(x,y)µÃµœlcp
//×¢: height[i] = lcp(sa[i], sa[i-1])
//sa[i]±íÊŸÅÅÃûÎªiµÄºó×ºÊÇË­£¬rank[i]±íÊŸŽÓs[i]¿ªÊŒµÄºó×ºÅÅÃûÊÇ¶àÉÙ
//sa,rank 0....n-1   height 1...n-1
//tmp ºÍtopÓÃÓÚ»ùÊýÅÅÐò£¬ŽóÐ¡ÒòÒªÅÅÐòµÄÊýµÄ·¶Î§¶ø¶š
//


char s[N];                          // N > 256
int n, sa[N], height[N], rank[N], tmp[N], top[N];
int x;
int st[20][N];

void SparseTable()
{
	for(int i=1;i<n;i++)
		st[0][i]=height[i];
	for(int j=1;(1<<j) <n;j++)
		for(int i=0; i+(1<<(j-1)) <n; i++)
			st[j][i]=min(st[j-1][i],st[j-1][i+(1<<(j-1))]);
}

void swap(int &x,int &y)
{
	if(x>y)
	{
		int t=x;
		x=y;
		y=t;
	}
}

int get(int x,int y)
{
	x=rank[x];y=rank[y];
	swap(x,y);
	x++;
	int k=int(log(double(y-x+1))/log(2.0));
	return min(st[k][x],st[k][y-(1<<k)+1]);
}
void makesa()
{                       // O(N * log N)
	int i, j, len, na;
	na = (n < 256 ? 256 : n);
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
	makesa();
	make_height();
	SparseTable();
	int l=1,r=n-1;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		int low,high;
		low=high=sa[1];
		bool flag=false;
		for(int i=1;i<n;i++)
		{
			if(height[i]<mid)
			{
				low=high=sa[i];
			}
			else
			{
				if(low>sa[i])	low=sa[i];
				if(high<sa[i])	high=sa[i];
				int len=high-low;
				if(len>=mid && low<=x && high>=x)
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
	return r;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	scanf("%s",s);
	n=strlen(s);
	x=n;
	s[n]='#';
	scanf("%s",s+n+1);
	n=strlen(s)+1;

	printf("%d\n",solve());
	return 0;
}
