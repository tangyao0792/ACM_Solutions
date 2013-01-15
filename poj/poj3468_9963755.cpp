#include<cstdio>
#include<cstring>

const int MAXN=100100;
typedef long long LL;

LL t[MAXN*4];
LL add[MAXN*4];

void PushUp(int pos,int l,int mid,int r)
{
    t[pos]=add[pos]*(r-l+1)
        +add[pos<<1]*(mid-l+1)
        +add[pos<<1|1]*(r-mid)
        +t[pos<<1]
        +t[pos<<1|1];
}
void PushDown(int pos)
{
    add[pos<<1]+=add[pos];
    add[pos<<1|1]+=add[pos];
    add[pos]=0;
}
void build(int l,int r,int pos)
{
    if(l==r)
    {
        scanf("%lld",&t[pos]);
        return;
    }
    int mid=(l+r)>>1;

    build(l,mid,pos<<1);
    build(mid+1,r,pos<<1|1);
    PushUp(pos,l,mid,r);
}

void update(int x,int y,LL z,int l,int r,int pos)
{
    if(x>r || y<l)
        return;
    if(x<=l && y>=r)
    {
        add[pos]+=z;
        return;
    }
    if(l==r)    return;
    PushDown(pos);
    int mid=(l+r)>>1;

    if(x<=mid)
        update(x,y,z,l,mid,pos<<1);
    if(y>mid)
        update(x,y,z,mid+1,r,pos<<1|1);

    PushUp(pos,l,mid,r);
}

LL query(int x,int y,int l,int r,int pos)
{
    if(x<=l && y>=r)
        return t[pos]+add[pos]*(r-l+1);

    if(x>r || y<l)
        return 0;

    int mid=(l+r)>>1;

    PushDown(pos);

    LL ans=0;
    if(x<=mid)
        ans+=query(x,y,l,mid,pos<<1);
    if(y>mid)
        ans+=query(x,y,mid+1,r,pos<<1|1);
    PushUp(pos,l,mid,r);
    return ans;

}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int n,q;
    char op[10];
    while(scanf("%d %d",&n,&q)==2)
    {
        memset(add,0,sizeof(add));
        build(1,n,1);
        for(int i=0;i<q;i++)
        {
            scanf("%s",op);
            if(op[0]=='Q')
            {
                int x,y;
                scanf("%d %d",&x,&y);
                printf("%lld\n",query(x,y,1,n,1));
            }
            else
            {
                int x,y;
                LL z;
                scanf("%d %d %lld",&x,&y,&z);
                update(x,y,z,1,n,1);
            }
        }
    }
    return 0;
}
