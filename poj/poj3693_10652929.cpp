#include<cstdio>
#include<cstring>
#include<cmath>

#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

//INIT: n = strlen(s) + 1;
//CALL: makesa(); lcp();SparseTable();get(x,y)得到lcp
//注: height[i] = lcp(sa[i], sa[i-1])
//sa[i]表示排名为i的后缀是谁，rank[i]表示从s[i]开始的后缀排名是多少
//rank 0....n-1   sa,height 1...n-1
//tmp 和top用于基数排序，大小因要排序的数的范围而定
//

const int N = 100100;

char s[N];                          // N > 256
int n, sa[N], height[N], rank[N], tmp[N], top[N];
int st[20][N];
int length[N];

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
			height[j] = (k--), j = rank[ sa[j] + 1 ];								}

void cmp(int &st,int &end,int &times,int l,int r,int t)
{
    if(t<times) return;
    if(t>times)
    {
        st=l;
        end=r;
        times=t;
        return;
    }
    int size=min(end-st,r-l)+1;
	for(int i=0;i<size;i++)
		if(s[st+i]>s[l+i])
		{
			st=l;
			end=r;
			return;
		}
		else if(s[st+i]<s[l+i])
        {
            return;
		}
    if(end-st>r-l)
    {
        st=l;
        end=r;
    }
}
void solve()
{
	n=strlen(s)+1;

	makesa();
	make_height();
	SparseTable();
	int st=0,end=0,times=0;
	int cnt=0;

	for(int len=n/2+1;len>=1;len--)
	{
		for(int i=0;i+len<n-1;i+=len)
		{
			int l=get(i,i+len);

            int x=(len-l%len)%len;
            int tmp=get(i-x,i-x+len);
            if(tmp<len) continue;
            int t=(x+len+tmp)/len;
            if(t>times)
            {
                times=t;
                cnt=0;
            }
            if(t==times)
            {
                length[cnt++]=len;
            }
		}
	}
    bool flag=true;
	for(int i=1;i<n && flag;i++)
	{
	    int a=sa[i];                //保证字典序
	    for(int j=0;j<cnt;j++)
	    {
	        if(a+length[j]>=n  )    continue;
	        int l=get(a,a+length[j]);
	        if((l+length[j])/length[j]>=times)
	        {
	            st=a;
	            end=a+length[j]*times-1;
	            flag=false;
	            break;
	        }

	    }
	}
	if(cnt==0)
	{
	    char ch='z';
	    for(int i=0;s[i];i++)
            ch=min(ch,s[i]);
        printf("%c\n",ch);
        return;
	}

	for(int i=st;i<=end;i++)
		printf("%c",s[i]);
	puts("");
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif

	int nCase=1;
	while(~scanf("%s",s))
	{
		if(s[0]=='#')	break;
		printf("Case %d: ",nCase++);
		solve();
	}

	return 0;
}
