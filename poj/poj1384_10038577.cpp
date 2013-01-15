#include<cstdio>

#define min(a,b) (a<b?a:b)

const int MAXN=510;
const int MAXM=10010;
const int INF=1<<28;

int dp[MAXM];
int p[MAXN],w[MAXN];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif

    int T;
    scanf("%d",&T);
    while(T--)
    {
        int e,f;
        scanf("%d %d",&e,&f);
        int V=f-e;
        int n;
        scanf("%d",&n);

        for(int i=1;i<=n;i++)
        {
            scanf("%d %d",&p[i],&w[i]);
        }

        for(int i=1;i<=V;i++)   dp[i]=INF;
        dp[0]=0;

        for(int i=1;i<=n;i++)
        {
            for(int v=w[i];v<=V;v++)
            {
                dp[v]=min(dp[v],dp[v-w[i]]+p[i]);
            }
        }

        if(dp[V]<INF)
        {
            printf("The minimum amount of money in the piggy-bank is %d.\n",dp[V]);
        }
        else
        {
            printf("This is impossible.\n");
        }
    }

    return 0;
}
