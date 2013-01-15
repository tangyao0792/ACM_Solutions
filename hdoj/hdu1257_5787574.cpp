/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

const int MAXN=1000010;
int dp[MAXN];
int h[MAXN];
int n;

inline int max(int a,int b){return a>b?a:b;}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r",stdin);
#endif

    while(scanf("%d",&n)==1)
    {
        for(int i=1;i<=n;i++)   scanf("%d",&h[i]);

        for(int i=1;i<=n;i++)   dp[i]=1;

        int ans=-1;

        for(int i=1;i<=n;i++)
            for(int j=1;j<i;j++)
                if(h[i]>h[j])
                    dp[i]=max(dp[i],dp[j]+1);

        for(int i=1;i<=n;i++)
            ans=max(ans,dp[i]);

        printf("%d\n",ans);
    }


    return 0;
}
