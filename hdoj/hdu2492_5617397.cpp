/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;

const int MAXN=100100;

int t[MAXN*4];
int a[MAXN];
int r[MAXN];        //indirected sort
int m[MAXN];        //
int lb[MAXN];       //left bigger
int ls[MAXN];       //left smaller

void PushUp(int pos)
{
    t[pos]=t[pos<<1]+t[pos<<1|1];
}

void update(int v,int l,int r,int pos)
{
    if(l==r)
    {
        if(l==v)
            t[pos]=1;
        return;
    }

    int mid=(l+r)>>1;

    if(v<=mid)
        update(v,l,mid,pos<<1);
    else
        update(v,mid+1,r,pos<<1|1);

    PushUp(pos);
}

int query(int a,int b,int l,int r,int pos)
{
    if(a>r || b<l)
        return 0;

    if(a<=l && b>=r)
    {
        return t[pos];
    }
    if(l==r)    return 0;

    int mid=(l+r)>>1;

    int ans=0;
    if(a<=mid)
        ans+=query(a,b,l,mid,pos<<1);
    if(b>mid)
        ans+=query(a,b,mid+1,r,pos<<1|1);

    return ans;
}

bool comp(int x,int y)
{
    return a[x]<a[y];
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int T,n;
    scanf("%d",&T);
    while(T--)
    {
        memset(t,0,sizeof(t));
        scanf("%d",&n);
        for(int i=0;i<n;i++)
        {
            scanf("%d",&a[i]);
            lb[i]=query(a[i],MAXN,1,MAXN,1);
            ls[i]=query(1,a[i],1,MAXN,1);
            update(a[i],1,MAXN,1);
        }
        for(int i=0;i<n;i++)    r[i]=i;
        sort(r,r+n,comp);

        for(int i=0;i<n;i++)    m[a[r[i]]]=i;

        long long ans=0;
        for(int i=0;i<n;i++)
        {
            long long tmp=lb[i];
            tmp=tmp*(m[a[i]]-ls[i]);
            ans+=tmp;

            tmp=ls[i];
            tmp=tmp*((n-m[a[i]]-1)-lb[i]);
            ans+=tmp;
        }
        printf("%I64d\n",ans);
    }
    return 0;
}
