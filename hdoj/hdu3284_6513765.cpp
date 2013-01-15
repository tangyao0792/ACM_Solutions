/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

int dp[111][2][111111];
int n,k;


int main(int argc, const char *argv[])
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int sn;
        scanf("%d %d %d",&sn,&n,&k);
        memset(dp,0,sizeof(0));
        dp[1][0][0]=dp[1][1][0]=1;
        for(int i=2;i<=n;i++)
            for(int j=0;j<=k;j++)
            {
                dp[i][1][j]=dp[i-1][1][j-1]+dp[i-1][0][j];
                dp[i][0][j]=dp[i-1][0][j]+dp[i-1][1][j];
                
            }
        printf("%d %d\n",sn,dp[n][0][k]+dp[n][1][k]);    
    }
    return 0;
}
