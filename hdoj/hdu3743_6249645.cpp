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

const int MAXN=1000100;

int a[MAXN],n;
int r[MAXN],rank[MAXN];        //a[r[i]] is th ith number
                            //rank[i] is a[i]'s rank

bool comp(int x,int y)
{
    return a[x]<a[y];
}

int ar[MAXN];
inline int lowb(int t){return t&(-t);}
void add(int i,int v)
{
    for(;i<=n;ar[i]+=v,i+=lowb(i));
}

int sum(int i)
{
    int s=0;
    for(;i>0;s+=ar[i],i-=lowb(i));
    return s;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif

    while(scanf("%d",&n)==1)
    {
        for(int i=0;i<n;i++)
        {
            scanf("%d",&a[i]);
            r[i]=i;
        }
        sort(r,r+n,comp);
        for(int i=0;i<n;i++)
            rank[r[i]]=i+1;

        long long ans=0;
        memset(ar,0,sizeof(ar));
        for(int i=0;i<n;i++)
        {
            ans+=sum(n)-sum(rank[i]);
            add(rank[i],1);
        }

        printf("%I64d\n",ans);

    }
    return 0;
}
