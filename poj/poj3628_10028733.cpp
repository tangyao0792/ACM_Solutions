#include<cstdio>
#include<cstring>

#define max(a,b) (a>b?a:b)

const int INF=1<<28;

int w[25];
int dp[20000010];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif

    int n;
    int b;
    while(scanf("%d %d",&n,&b)==2)
    {
        int sum=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&w[i]);
            sum+=w[i];
        }
        dp[0]=0;

        for(int i=1;i<=sum;i++)   dp[i]=-INF;

        for(int i=1;i<=n;i++)
        {
            for(int v=sum;v>=w[i];v--)
            {
                dp[v]=max(dp[v],dp[v-w[i]]+1);
            }
        }
        for(int v=b;;v++)
            if(dp[v]>0)
            {
                printf("%d\n",v-b);
                break;
            }
    }

    return 0;
}
