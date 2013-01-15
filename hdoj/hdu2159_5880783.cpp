/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)

const int MAXN=110;
const int MAXV=20*MAXN;
const int INF=1<<28;

int dp[MAXV][MAXN];
int c[MAXN],w[MAXN];
int n,m,k,s;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r",stdin);
#endif

    while(scanf("%d %d %d %d",&n,&m,&k,&s)==4 )
    {
        for(int i=1;i<=k;i++)
            scanf("%d %d",&c[i],&w[i]);

//        for(int j=0;j<=s;j++)
//            for(int kk=0;kk<=n;kk++)
//                dp[kk][j]=INF;
//        for(int kk=0;kk<=n;kk++)
//            dp[kk][0]=0;
        memset(dp,0,sizeof(dp));

        for(int i=1;i<=k;i++)
            for(int j=1;j<=s;j++)
                for(int kk=w[i];kk<=m;kk++)
                    dp[kk][j]=
                    max(dp[kk][j],dp[kk-w[i]][j-1]+c[i]);

        int ans=-1;
        for(int i=0;i<=m;i++)
            if(dp[i][s]>=n)
            {
                ans=m-i;
                break;
            }

        if(ans<0)
            ans=-1;
        printf("%d\n",ans);
    }

    return 0;
}
