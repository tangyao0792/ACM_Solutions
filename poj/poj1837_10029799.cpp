#include<cstdio>
#include<cstring>

int l[21],w[21];
int dp[21][15010];
const int offset=7500;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    int c,g;
    while(scanf("%d %d",&c,&g)==2)
    {
        for(int i=1;i<=c;i++)   scanf("%d",&l[i]);
        for(int i=1;i<=g;i++)   scanf("%d",&w[i]);

        memset(dp,0,sizeof(dp));

        for(int i=1;i<=c;i++)
            dp[1][w[1]*l[i]+offset]++;

        for(int i=2;i<=g;i++)
        {
            for(int j=1;j<=c;j++)
            {
                int tmp=l[j]*w[i];
                for(int k=0;k<=15000;k++)
                {
                    if(k+tmp>=0 && k+tmp<=15000)
                    {
                        dp[i][k+tmp]+=dp[i-1][k];
                    }
                }
            }
        }

        printf("%d\n",dp[g][offset]);
    }
    return 0;
}
