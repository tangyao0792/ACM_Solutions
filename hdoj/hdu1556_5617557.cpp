/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
//Color the ball hdu1556

#include<cstdio>
#include<cstring>

const int MAXN=100100;

int t[MAXN*4];

void PushDown(int pos)
{
    t[pos<<1]+=t[pos];
    t[pos<<1|1]+=t[pos];
    t[pos]=0;
}

void update(int a,int b,int l,int r,int pos)
{
    if(a>r || b<l)
        return;

    if(a<=l && b>=r)
    {
        t[pos]++;
        return;
    }
    if(l==r)    return;

    int mid=(l+r)>>1;

    PushDown(pos);

    if(a<=mid)
        update(a,b,l,mid,pos<<1);
    if(b>mid)
        update(a,b,mid+1,r,pos<<1|1);
}

int query(int v,int l,int r,int pos)
{
    if(l==r)
    {
        if(v==l)
            return t[pos];
        return 0;
    }
    PushDown(pos);

    int mid=(l+r)>>1;

    if(v<=mid)
        return query(v,l,mid,pos<<1);

    return query(v,mid+1,r,pos<<1|1);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int n;
    while(scanf("%d",&n)==1 && n)
    {
        memset(t,0,sizeof(t));
        for(int i=0;i<n;i++)
        {
            int a,b;
            scanf("%d %d",&a,&b);
            update(a,b,1,n,1);
        }
        printf("%d",query(1,1,n,1));
        for(int i=2;i<=n;i++)
            printf(" %d",query(i,1,n,1));
        printf("\n");
    }
    return 0;
}
