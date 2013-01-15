/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

const int MAXN=110;
const double EPS=1e-12;

double p[MAXN];         //被抓的概率
int c[MAXN];
double dp[MAXN*100];
int n;
double P;

double max(double a,double b)
{
    if(a>b+EPS) return a;
    return b;
}

int solve(int V)
{
    for(int i=0;i<=V;i++)   dp[i]=0;
    dp[0]=1;
    for(int i=1;i<=n;i++)
    {
        for(int v=V;v>=c[i];v--)
        {
            dp[v]=max(dp[v],dp[v-c[i]]*p[i]);
        }
    }

    for(int v=V;v>=0;v--)
        if(dp[v]>P+EPS)
            return v;
    return 0;

}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r",stdin);
#endif
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lf %d",&P,&n);
        P=1-P;
        int V=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%d %lf",&c[i],&p[i]);
            p[i]=1-p[i];
            V+=c[i];
        }

        printf("%d\n",solve(V));
    }
    return 0;
}
