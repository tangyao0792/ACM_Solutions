/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

#define max(a,b) (a>b?a:b)

const int MAXN=200010;

int x[MAXN];    //临时存储一行的数据
int y[MAXN];    //每行的最优情况
int dp[MAXN];

int n,m;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif

    while(scanf("%d %d",&n,&m)==2)
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                scanf("%d",&x[j]);
            }
            dp[1]=x[1];
            for(int j=2;j<=m;j++)
                dp[j]=max(dp[j-2]+x[j],dp[j-1]);
            y[i]=dp[m];
        }

        dp[1]=y[1];
        for(int j=2;j<=n;j++)
            dp[j]=max(dp[j-2]+y[j],dp[j-1]);

        printf("%d\n",dp[n]);
    }

    return 0;
}
