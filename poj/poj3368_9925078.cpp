#include<cstdio>
#include<cstring>
#include<cmath>

#define max(a,b) (a>b?a:b)

const int MAXN=100010;

int st[MAXN][20];
int a[MAXN],b[MAXN],c[MAXN];
//a记录原数组，b[i]记录a[i]与左边元素相同的个数
//c[i]记录a[i]与两边元素相同的个数

int n,q;

void SparseTable()
{
    for(int i=1;i<=n;i++)   st[i][0]=b[i];
    for(int j=1;1+(1<<j)<=n;j++)
        for(int i=1;i+(1<<(j-1))<=n;i++)
            st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
}

int getMax(int l, int r)
{
    if(b[r]>=r-l+1)  return r-l+1;
    int tmp=c[l]-b[l]+1;
    int x=l+tmp;
    int y=r;

    if(x>=y)    return tmp;
    int k=int(log(double (y-x+1))/log(2.0));
    tmp= max(tmp,max(st[x][k],st[1+y-(1<<k)][k]));
    return tmp;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d",&n)==1 && n)
    {
        scanf("%d",&q);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        b[1]=c[n]=1;
        for(int i=2;i<=n;i++)
        {
            if(a[i]==a[i-1])
                b[i]=b[i-1]+1;
            else
                b[i]=1;
        }
        c[n]=b[n];
        for(int i=n-1;i>0;i--)
        {
            if(a[i]==a[i+1])
            {
                c[i]=c[i+1];
            }
            else
                c[i]=b[i];
        }
        SparseTable();
        for(int i=0;i<q;i++)
        {
            int x,y;
            scanf("%d %d",&x,&y);
            printf("%d\n",getMax(x,y));
        }
    }
    return 0;
}
