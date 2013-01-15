/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

#define max(a,b) (a>b?a:b)

const int MAXN=1010;

int w[MAXN];
long long d[MAXN];
int n;

long long dp()
{
    d[0]=0;
    for(int i=1;i<=n;i++)   d[i]=w[i];

    for(int i=n;i>=0;i--)
        for(int j=n;j>i;j--)
            if(w[i]<w[j])
                d[i]=max(d[i],d[j]+w[i]);
    return d[0];
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    while(scanf("%d",&n)==1 && n)
    {
        for(int i=1;i<=n;i++)    scanf("%d",&w[i]);
        printf("%I64d\n",dp());
    }
    return 0;
}
