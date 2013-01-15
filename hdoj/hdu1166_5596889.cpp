/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

const int MAXN=55555;

int sum[MAXN<<2];

void pushup(int pos)
{
    sum[pos]=sum[pos<<1]+sum[pos<<1|1];
}

void build(int l,int r,int pos)
{
    if(l==r)
    {
        scanf("%d",&sum[pos]);
        return;
    }
    int mid=(l+r)>>1;

    build(l,mid,pos<<1);
    build(mid+1,r,pos<<1|1);
    pushup(pos);
}

void update(int p,int v,int l,int r,int pos)
{
    if(l==r)
    {
        sum[pos]+=v;
        return;
    }
    int mid=(l+r)>>1;
    if(p<=mid)
        update(p,v,l,mid,pos*2);
    else
        update(p,v,mid+1,r,pos*2+1);

    pushup(pos);
}

int query(int a,int b,int l,int r,int pos)
{
    if(a<=l && b>=r)
    {
        return sum[pos];
    }
    int mid=(l+r)>>1;
    int ret=0;
    if(a<=mid)
        ret+=query(a,b,l,mid,pos<<1);
    if(b>mid)
        ret+=query(a,b,mid+1,r,pos<<1|1);
    return ret;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif

    int T,n,a,b;
    char s[100];
    scanf("%d",&T);
    for(int i=1;i<=T;i++)
    {
        printf("Case %d:\n",i);
        scanf("%d",&n);
        build(1,n,1);
        while(~scanf("%s",s))
        {
            if(s[0]=='E')   break;
            scanf("%d %d",&a,&b);
            if(s[0]=='A')
            {
                update(a,b,1,n,1);
            }
            else if(s[0]=='S')
            {
                update(a,-b,1,n,1);
            }
            else
            {
                printf("%d\n",query(a,b,1,n,1));
            }
        }
    }

    return 0;
}
