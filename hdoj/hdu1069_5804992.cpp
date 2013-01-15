/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

#define max(a,b) (a>b?a:b)

typedef long long LL;

const int MAXN=35;

int t[MAXN][3];
int dx[3]={0,1,2};
int dy[3]={1,2,0};
int dz[3]={2,0,1};

LL dp[MAXN][3];
int n;

LL dfs(int cur,int x,int y,int z)
{
    if(dp[cur][z])
        return dp[cur][z];
    LL ans=0;
    for(int i=1;i<=n;i++)
        for(int j=0;j<3;j++)
            if((t[i][dx[j]]>t[cur][x] && t[i][dy[j]]>t[cur][y])
               ||(t[i][dx[j]]>t[cur][y] && t[i][dy[j]]>t[cur][x]))
            {
                LL tmp=dfs(i,dx[j],dy[j],dz[j]);
                ans=max(ans,tmp);
            }

    return dp[cur][z]=ans+t[cur][z];
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r",stdin);
#endif
    int nCase=0;
    while(scanf("%d",&n)==1 && n)
    {
        nCase++;
        for(int i=1;i<=n;i++)
            scanf("%d %d %d",&t[i][0],&t[i][1],&t[i][2]);

        LL ans=0;
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
        {
            for(int j=0;j<3;j++)
            {
                LL tmp=dfs(i,dx[j],dy[j],dz[j]);
                ans=max(ans,tmp);
            }
        }

        printf("Case %d: maximum height = %I64d\n",nCase,ans);
    }
    return 0;
}
