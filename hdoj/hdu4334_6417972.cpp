/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

const int MAXN=222;

typedef long long LL;

LL a[MAXN],b[MAXN],c[MAXN],d[MAXN],e[MAXN];
LL sum1[MAXN*MAXN],sum2[MAXN*MAXN];

int n,p;

bool find(LL x)
{
    int p1=0,p2=p-1;
    while(true)
    {
        LL tmp=sum1[p1]+sum2[p2];
        if(tmp == x)
            return true;
        if(p1==p-1 && p2>0)
        {
            p2--;
            continue;
        }
        if(p2==0 && p1<p-1)
        {
            p1++;
            continue;
        }
        if(p1==p-1 && p2==0)
            break;
        if(tmp>x)
            p2--;
        else
            p1++;

    }
    return false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r",stdin);
#endif
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i=0;i<n;i++) scanf("%I64d",&a[i]);
        for(int i=0;i<n;i++) scanf("%I64d",&b[i]);
        for(int i=0;i<n;i++) scanf("%I64d",&c[i]);
        for(int i=0;i<n;i++) scanf("%I64d",&d[i]);
        for(int i=0;i<n;i++) scanf("%I64d",&e[i]);

        p=0;
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
            {
                sum1[p]=a[i]+b[j];
                sum2[p++]=c[i]+d[j];
            }

        sort(sum1,sum1+p);
        sort(sum2,sum2+p);

        bool flag=false;

        for(int i=0;i<n;i++)
        {
            if(find(-e[i]))
            {
                flag=true;
                break;
            }
        }
        if(flag)
            puts("Yes");
        else
            puts("No");

    }
    return 0;
}
