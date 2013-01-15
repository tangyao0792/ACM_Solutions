/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>

#define max(a,b) (len[a]>=len[b]?a:b)
#define min(a,b) (a<b?a:b)

const int MAXN=200200;

int t[MAXN*4];
int len[MAXN];
int h,w,n;

void PushUp(int pos)
{
    t[pos]=max(t[pos<<1],t[pos<<1|1]);
}

void build(int l,int r,int pos)
{
    if(l==r)
    {
        t[pos]=l;
        len[l]=w;
        return;
    }
    int mid=(l+r)>>1;

    build(l,mid,pos<<1);
    build(mid+1,r,pos<<1|1);

    PushUp(pos);
}

int query(int v,int l,int r,int pos)
{

    if(l==r)
    {
        if(len[t[pos]]>=v)
        {
            len[t[pos]]-=v;
            return t[pos];
        }
        return -1;
    }

    int mid=(l+r)>>1;
    int ans;
    if(len[t[pos<<1]]>=v)
        ans=query(v,l,mid,pos<<1);
    else
        ans=query(v,mid+1,r,pos<<1|1);

    PushUp(pos);

    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif

    while(scanf("%d %d %d",&h,&w,&n)==3)
    {
        int t=min(n,h);
        build(1,t,1);
        for(int i=0;i<n;i++)
        {
            int l;
            scanf("%d",&l);
            printf("%d\n",query(l,1,t,1));
        }
    }

    return 0;
}
