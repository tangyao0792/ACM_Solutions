/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

typedef long long ll;

ll dp[1<<19][19];
int g[19][19];
int pre[19];
int n,m;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    pre[0]=1;
    for(int i=1;i<19;i++)
        pre[i]=pre[i-1]<<1;

    while(scanf("%d %d",&n,&m)==2)
    {
        memset(g,0,sizeof(g));
        for(int i=0;i<m;i++)
        {
            int x,y;
            scanf("%d %d",&x,&y);
            if(x==y)    continue;
            x--,y--;
            g[x][y]=g[y][x]=1;
        }
        int maxs=pre[n];
        for(int i=0;i<maxs;i++)
            for(int j=0;j<n;j++)
                dp[i][j]=0;
        dp[1][0]=1;         //从0出发的初始化

//dp[s][k]表示状态为s，当前beed为k的路数
//dp[s][k]=求和dp[son][j];
//条件g[j][k]==1
//s=son|(1<<k);


        for(int son=1;son<maxs;son++)
        {
            for(int j=0;j<n;j++)
            {
                if((son&(pre[j]))==0)   continue;
                for(int k=0;k<n;k++)
                {
                    if(g[j][k] && (son&(pre[k]))==0)
                    {
                        dp[son|(pre[k])][k]+=dp[son][j];
                    }
                }
            }
        }
        ll ans=0;
        for(int i=1;i<n;i++)
            if(g[i][0])
                ans+=dp[maxs-1][i];

        printf("%I64d\n",ans);
    }

    return 0;
}
