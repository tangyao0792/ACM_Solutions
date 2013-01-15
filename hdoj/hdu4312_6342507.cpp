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

typedef long long LL;

const int MAXN=100010;

int n;
LL arx[MAXN];
LL ary[MAXN];

inline int lowb(int t)    {return t&(-t);}
void add(LL *ar,int i,LL v)
{
    for(;i<=n;ar[i]+=v,i+=lowb(i));
}
LL sum(LL *ar,int i)
{
    LL s=0;
    for(;i>0;s+=ar[i],i-=lowb(i));
    return s;
}

LL x[MAXN],y[MAXN];
int px[MAXN],py[MAXN],rx[MAXN],ry[MAXN];

bool compx(int a,int b)
{
    return x[a]<x[b];
}
bool compy(int a,int b)
{
    return y[a]<y[b];
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            scanf("%I64d %I64d",&x[i],&y[i]);
            //scanf("%lld %lld",&x[i],&y[i]);
            int nx=x[i]-y[i];
            int ny=x[i]+y[i];
            x[i]=nx;y[i]=ny;
            rx[i]=ry[i]=i;
        }
        sort(rx+1,rx+n+1,compx);
        sort(ry+1,ry+n+1,compy);
        for(int i=1;i<=n;i++)
        {
            px[rx[i]]=i;
            py[ry[i]]=i;
        }
        memset(arx,0,sizeof(arx));
        memset(ary,0,sizeof(ary));
        for(int i=1;i<=n;i++)
        {
            add(arx,i,x[rx[i]]);
            add(ary,i,y[ry[i]]);
        }
        LL ans=-1;
        LL tmpx=sum(arx,n);
        LL tmpy=sum(ary,n);
        for(int i=1;i<=n;i++)
        {
            LL tmpx1=sum(arx,px[i]-1);
            LL tmpx2=tmpx-tmpx1-x[i];
            LL sumx=x[i]*(px[i]-1)-tmpx1+tmpx2-x[i]*(n-px[i]);

            LL tmpy1=sum(ary,py[i]-1);
            LL tmpy2=tmpy-tmpy1-y[i];
            LL sumy=y[i]*(py[i]-1)-tmpy1+tmpy2-y[i]*(n-py[i]);
            if(ans==-1 || ans>sumx+sumy)
            {
                ans=sumx+sumy;
            }
        }
        printf("%I64d\n",ans/2);
    }
    return 0;
}
