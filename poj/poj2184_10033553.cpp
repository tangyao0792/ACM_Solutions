#include<cstdio>
#include<cstring>

#define max(a,b) (a>b?a:b)

const int INF=1<<28;
const int MAXN=110;
const int MAXM=2000*MAXN;

int s[MAXN],f[MAXN];
int dp[MAXM];
int tot[MAXM];
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif

    int n;
    while(scanf("%d",&n)==1)
    {
        int sum=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%d %d",&s[i],&f[i]);
            if(s[i]<=0 && f[i]<=0)
            {
                i--,n--;
                continue;
            }
            s[i]+=1000;
            sum+=s[i];
        }

        for(int i=1;i<=sum;i++)
        {
            dp[i]=-INF;
            tot[i]=0;
        }
        dp[0]=0;
//dp[v]表示
        for(int i=1;i<=n;i++)
            for(int v=sum;v>=s[i];v--)
                if(dp[v]-tot[v]*1000 <
                   dp[v-s[i]]+f[i]-(1+tot[v-s[i]])*1000)
                {
                    dp[v]=dp[v-s[i]]+f[i];
                    tot[v]=tot[v-s[i]]+1;
                }

        int nMax=0;

        for(int v=0;v<=sum;v++)
            if(v-tot[v]*1000>=0 &&
               dp[v]>=0 &&
               nMax<dp[v]+v-tot[v]*1000)
            {
                nMax=dp[v]+v-tot[v]*1000;
            }

        printf("%d\n",nMax);
    }

    return 0;
}
