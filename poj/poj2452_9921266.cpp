#include<cstdio>
#include<cstring>
#include<cmath>




#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

const int MAXN=50010;

int n;
int stMax[MAXN][18],stMin[MAXN][18],l[MAXN];
int maxrmq(int i,int j){return(l[i]>l[j]?i:j);}
int minrmq(int i,int j){return(l[i]<l[j]?i:j);}

void st()
{
    for(int i=1;i<=n;i++)   stMax[i][0]=stMin[i][0]=i;

    for(int j=1;(1<<j) <= n; j++)
    {
        for(int i=1;i+(1<<(j-1))<=n;i++)
        {
            stMax[i][j]=maxrmq(stMax[i][j-1],stMax[i+(1<<(j-1))][j-1]);
            stMin[i][j]=minrmq(stMin[i][j-1],stMin[i+(1<<(j-1))][j-1]);
        }
    }
}
int getMax(int x, int y)
{
    int k=int(log(double (y-x+1))/log(2.0));

    return maxrmq(stMax[x][k],stMax[1+y-(1<<k)][k]);
}
int getMin(int x, int y)
{
    int k=int(log(double (y-x+1))/log(2.0));

    return minrmq(stMin[x][k],stMin[1+y-(1<<k)][k]);
}

int solve(int x)
{
    int left=x+1,right=n;
    int mid;
    while(left<right)
    {
        mid=(left+right)>>1;
        if(l[getMin(left,mid)]>l[x])
            left=mid+1;
        else
            right=mid-1;
    }
    return getMax(x,left);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    while(scanf("%d",&n)==1)
    {
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&l[i]);
        }
        st();
        int nMax=0;
//        for(int i=1;i<=n;i++)
//        {
//            int right=getMax(i,n);
//            int left=getMin(i,right);
//                nMax=max(nMax,right-left);
//        }
//这么做不能保证最大区间一定被找到

        for(int i=1;i<=n;i++)
        {
            int tmp=solve(i)-i;
            nMax=max(nMax,tmp);
        }
        if(nMax)
            printf("%d\n",nMax);
        else
            printf("-1\n");
    }
    return 0;
}
