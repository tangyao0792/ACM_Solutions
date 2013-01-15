/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>


const int MAXN=2000100;

int mark[MAXN*4];
int n,m;

int max(int a,int b)
{
    if(a>b)
        return a;
    return b;
}

void PushUp(int pos)
{
    mark[pos]=max(mark[pos<<1],mark[pos<<1|1]);
}

void build(int l,int r,int pos)
{
    if(l==r)
    {
        scanf("%d",&mark[pos]);
        return;
    }
    int mid=(l+r)>>1;

    build(l,mid,pos<<1);
    build(mid+1,r,pos<<1|1);

    PushUp(pos);
}

void update(int p,int v,int l,int r,int pos)
{
    if(l==r)
    {
        if(l==p)
            mark[pos]=v;

        return;
    }

    int mid=(l+r)>>1;

    if(p<=mid)
        update(p,v,l,mid,pos<<1);
    else
        update(p,v,mid+1,r,pos<<1|1);

    PushUp(pos);
}

int query(int a,int b,int l,int r,int pos)
{
    if(a<=l && b>=r)
    {
        return mark[pos];
    }
    int mid=(l+r)>>1;

    int ret=-1;
    if(b<=mid)
        ret=max(ret,query(a,b,l,mid,pos<<1));
    else if(a>mid)
        ret=max(ret,query(a,b,mid+1,r,pos<<1|1));
    else
    {
        ret=max(ret,query(a,b,mid+1,r,pos<<1|1));
        ret=max(ret,query(a,b,l,mid,pos<<1));
    }
    return ret;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif

    while(scanf("%d %d",&n,&m)==2)
    {
        build(1,n,1);
        for(int i=0;i<m;i++)
        {
            char c[5];int x,y;
            scanf("%s %d %d\n",c,&x,&y);
            if(c[0]=='Q')
            {
                printf("%d\n",query(x,y,1,n,1));
            }
            else
            {
                update(x,y,1,n,1);
            }
        }
    }
    return 0;
}
