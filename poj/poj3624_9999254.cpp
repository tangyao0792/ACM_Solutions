#include<cstdio>
#include<cstring>

#define max(a,b) (a>b?a:b)

const int MAXM=13000;
const int MAXN=3500;

int dp[MAXM];
int w[MAXN],c[MAXN];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int n,m;
    while(scanf("%d %d",&n,&m)==2)
    {
        memset(dp,0,sizeof(dp));
        for(int i=0;i<n;i++)
            scanf("%d %d",&c[i],&w[i]);

        for(int i=0;i<n;i++)
            for(int v=m;v>=0;v--)
            {
                if(v>=c[i])
                    dp[v]=max(dp[v],dp[v-c[i]]+w[i]);
            }
        printf("%d\n",dp[m]);
    }
    return 0;
}
