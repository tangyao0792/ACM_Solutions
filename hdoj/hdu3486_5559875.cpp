/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>
#include<cmath>

#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

const int MAXN=200010;

int st[20][MAXN];
int n,k;

void SparseTable()
{
    for(int j=1;(1<<j) <n;j++)
        for(int i=0; i+(1<<(j-1)) <n; i++)
            st[j][i]=max(st[j-1][i],st[j-1][i+(1<<(j-1))]);
}

int get(int x,int y)
{
    int k=int(log(double(y-x+1))/log(2.0));

    return max(st[k][x],st[k][y-(1<<k)+1]);
}

int solve(int l, int r)
{
    if(l<=0) l=1;
    if(r>n) r=n;
    for(int i=l;i<=r;i++)
    {
        int sum=0;
        int step=n/i;
        int p=0;
        for(int j=0;j+step-1<n;j+=step)
        {
            sum+=get(j,j+step-1);
            p++;
            if(sum>k)
                return p;
        }
    }
    return -1;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d %d",&n,&k)==2)
    {
        if (n < 0 && k < 0)
            break;
        long long sum=0;
        int nMax=0;
        int nMin=1001;
        for(int i=0;i<n;i++)
        {
            scanf("%d",&st[0][i]);
            sum+=st[0][i];
            nMax=max(nMax,st[0][i]);
            nMin=min(nMin,st[0][i]);
        }
        if(nMin<=0) nMin=1;
        if(sum <=k)
        {
            printf("-1\n");
            continue;
        }
        if(nMax>k)
        {
            printf("1\n");
            continue;
        }
        SparseTable();
        printf("%d\n",solve((k/nMax)-1,(k/nMin)+1));
    }
    return 0;
}
