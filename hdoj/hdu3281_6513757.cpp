/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>
#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)

const int INF=1<<28;

int dp[1111][55];

int main(int argc, const char *argv[])
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    int B=50,M=1000;
    for(int i=0;i<=M;i++)
        for(int j=0;j<=B;j++)
            dp[i][j]=INF;

        for(int i=1;i<=M;i++)
            dp[i][1]=i;
        for(int i=0;i<=B;i++)
            dp[1][i]=1;

        for(int i=2;i<=M;i++)
            for(int j=2;j<=B;j++)
                for(int k=1;k<=i;k++)
                {
                    if(k==1)
                        dp[i][j]=min(dp[i][j],dp[i-k][j]+1);
                    else if(k==i)
                        dp[i][j]=min(dp[i][j],dp[k-1][j-1]+1);
                    else
                        dp[i][j]=min(dp[i][j],max(dp[k-1][j-1],dp[i-k][j])+1);
                }


    int T;

    scanf("%d",&T);
    while(T--)
    {
        int sn;
        scanf("%d %d %d",&sn,&B,&M);
        if(B==1)
            printf("%d %d\n",sn,M);
        else
            printf("%d %d\n",sn,dp[M][B]);
    }
    return 0;
}
