#include<cstdio>
#include<cstring>

#define max(a,b) (a>b?a:b)

const int MAXM=1000000*50/1000;

int V,Y;
int c[11],w[11];
int dp[MAXM];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif

    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&V,&Y);
        int d;
        scanf("%d",&d);
        for(int i=1;i<=d;i++)
        {
            scanf("%d %d",&c[i],&w[i]);
            c[i]/=1000;
        }
        int tmp=V%1000;
        V=V/1000;
        for(int y=0;y<Y;y++)
        {
            memset(dp,0,sizeof(dp));
            for(int i=1;i<=d;i++)
            {
                for(int v=c[i];v<=V;v++)
                    dp[v]=max(dp[v],dp[v-c[i]]+w[i]);
            }
            tmp+=dp[V];
            V+=tmp/1000;
            tmp=tmp%1000;
        }
        printf("%d\n",V*1000+tmp);
    }
    return 0;
}
