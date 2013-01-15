/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

#define max(a,b) (a>b?a:b)

const int MAXN=101;
const int MAXV=3000010;

int dp[MAXV];
int w[MAXN];
int a[3];
int q,n,m,cnt;

double solve()
{
    memset(dp,0,sizeof(dp));

    for(int i=1;i<=cnt;i++)
    {
        for(int v=q;v>=w[i];v--)
        {
            dp[v]=max(dp[v],dp[v-w[i]]+w[i]);
        }
    }
    return double(dp[q])/100.0;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r",stdin);
#endif
    double t;
    while(scanf("%lf %d",&t,&n)==2)
    {
        if(n==0)    break;
        q=int(t*100);
        cnt=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&m);
            memset(a,0,sizeof(a));
            char c;
            bool f=true;
            for(int j=0;j<m;j++)
            {
                scanf(" %c:%lf",&c,&t);
                if(c=='A')  a[0]+=t*100;
                else if(c=='B') a[1]+=t*100;
                else if(c=='C') a[2]+=t*100;
                else f=false;
            }
            int sum=0;
            for(int j=0;j<3;j++)
            {
                sum+=a[j];
                if(a[j]>60000)
                    f=false;
            }
            if(sum>100000)
                f=false;
            if(!f)
            {
            }
            else
            {
                cnt++;
                w[i]=sum;
            }
        }
        printf("%.2f\n",solve());
    }
    return 0;
}
