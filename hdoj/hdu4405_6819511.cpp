/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

using namespace std;

const int MAXN=100100;

double dp[MAXN];
int next[MAXN];
int n,m;

inline int find(int x)
{
    if(next[x]==0)
        return x;
    return next[x]=find(next[x]);
}

int main(int argc, const char *argv[])
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    while(scanf("%d %d",&n,&m)==2)
    {
        if(n==0 && m==0)
            break;
        memset(next,0,sizeof(next));
        for(int i=0;i<m;i++)
        {
            int x,y;
            scanf("%d %d",&x,&y);
            next[x]=y;
        }
        for(int i=0;i<=n;i++)
        {
            if(next[i])
                find(i);
//            printf(" %d",next[i]);
        }
//        puts("");

        memset(dp,0,sizeof(dp));
        for(int i=n-1;i>=0;i--)
        {
            if(next[i])
            {
                dp[i]=dp[next[i]];
            }
            else
            {
                for(int j=1;j<=6;j++)
                {
                    dp[i]+=dp[i+j]+1;
                }
                dp[i]/=6;
            }
        }
        printf("%.4f\n",dp[0]);
    }
    return 0;
}
