/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

const int MAXN=100010;

int n,m;
long long t[MAXN*4],maxt[MAXN*4],mint[MAXN*4];

inline void pushup(int pos)
{
    if(t[pos<<1]==t[pos<<1|1])
        t[pos]=t[pos<<1];
    else
        t[pos]=-1;
    maxt[pos]=max(maxt[pos<<1],maxt[pos<<1|1]);

    mint[pos]=min(mint[pos<<1],mint[pos<<1|1]);
}
inline void pushdown(int pos)
{
    if(t[pos]!=-1)
    {
        t[pos<<1]=t[pos<<1|1]=t[pos];
        maxt[pos<<1]=maxt[pos<<1|1]=t[pos];
        mint[pos<<1]=mint[pos<<1|1]=t[pos];
    }
}
void build(int l,int r,int pos)
{
    if(l==r)
    {
        scanf("%I64d",&t[pos]);
        maxt[pos]=mint[pos]=t[pos];
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,pos<<1);
    build(mid+1,r,pos<<1|1);
    pushup(pos);
}

void update(int a,int b,long long v,int l,int r,int pos)
{
    if(a<=l && r<=b)
    {
        maxt[pos]=mint[pos]=t[pos]=v;
        return;
    }
    pushdown(pos);
    int mid=(l+r)>>1;
    if(a<=mid)
        update(a,b,v,l,mid,pos<<1);
    if(b>mid)
        update(a,b,v,mid+1,r,pos<<1|1);
    pushup(pos);
}

int query(int a,int b,long long v,int l,int r,int pos)
{
    if(a<=l && r<=b)
    {
        if(maxt[pos]<v || mint[pos]>v)  return 0;
        if(t[pos]!=-1)
        {
            if(t[pos]==v)    return r-l+1;
            return 0;
        }
    }

    pushdown(pos);

    int ans=0;
    int mid=(l+r)>>1;
    if(a<=mid)
        ans+=query(a,b,v,l,mid,pos<<1);
    if(b>mid)
        ans+=query(a,b,v,mid+1,r,pos<<1|1);
    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    while(scanf("%d %d",&n,&m)==2)
    {
        build(1,n,1);
        int a,l,r;
        long long z;
        for(int i=0;i<m;i++)
        {
            scanf("%d %d %d %I64d",&a,&l,&r,&z);
            l++,r++;
            if(a==1)
                update(l,r,z,1,n,1);
            else
                printf("%d\n",query(l,r,z,1,n,1));
        }
    }
    return 0;
}
