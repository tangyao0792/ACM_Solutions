#include<cstdio>
#include<cstring>
#include<cmath>
#define max(a,b) (a>b?a:b)

const int N=500000;
const int INF=1<<28;
 int prm[9]={2,3,5,7,11,13,17,23,29};

int cp[N+1];        //反素数
int num[N+1];

void counterPrime()
{
    for(int i=1;i<=N;i++)
    {
        num[i]=1;
        int last=INF;
        int tmp=i;
        for(int k=0;k<9;k++)
        {
            int t=0;
            while(tmp%prm[k]==0)
            {
                t++;
                tmp/=prm[k];
            }
            if(t>last)
                break;
            else
                last=t;
            num[i]*=(t+1);
        }
        if(num[i]>num[cp[i-1]])
            cp[i]=i;
        else
            cp[i]=cp[i-1];

    }
}

int n,k;
int t[N*4];

void build(int l,int r,int pos)
{
	t[pos]=r-l+1;
	if(l==r)	return;
	int mid=(l+r)>>1;
	build(l,mid,pos<<1);
	build(mid+1,r,pos<<1|1);
}

int query(int a,int b,int l,int r,int pos)
{
    if(a>b)  return 0;
    if(a<=l && r<=b)
    {
        return t[pos];
    }
    int mid=(l+r)>>1;

    int ans=0;
    if(a<=mid)
        ans+=query(a,b,l,mid,pos<<1);
    if(b>mid)
        ans+=query(a,b,mid+1,r,pos<<1|1);
    return ans;
}

int update(int v,int l,int r,int pos)
{
    while(true)
	{
		t[pos]--;
		if(l==r)break;
		int mid=(l+r)>>1;
		if(v<=t[pos<<1])
		{
			r=mid;
			pos=pos<<1;
		}
		else
		{
			v-=t[pos<<1];
			l=mid+1;
			pos=pos<<1|1;
		}
	}
	return l;
}

int a[N];
char name[N][20];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	counterPrime();
	while(scanf("%d %d",&n,&k)==2)
	{
	    build(1,n,1);
	    for(int i=1;i<=n;i++)
	    {
	        scanf("%s %d",name[i],&a[i]);
	    }
	    int pos=cp[n];

	    update(k,1,n,1);

	    for(int i=1;i<pos;i++)
	    {
	        int next;
	        if(a[k]>0)
                next=((a[k]-1)%(n-i)+(n-i))%(n-i);
	        else
                next=((a[k])%(n-i)+(n-i))%(n-i);
	        int rsum=query(k,n,1,n,1);
	        int lsum=(n-i)-rsum;

	        if(next<rsum)
                k=update(next+lsum+1,1,n,1);
            else
                k=update(next-rsum+1,1,n,1);
	    }

	    printf("%s %d\n",name[k],num[cp[n]]);
	}
	return 0;
}
