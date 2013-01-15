#include<cstdio>
#include<cstring>

const int MAXN=15010;
const int MAX=32010;

int a[MAXN];
int t[MAX*4];
int level[MAXN];


int query(int a,int b,int l,int r,int pos)
{
    if(a<=l && b>=r)
        return t[pos];

    if(a>r || b<l)
        return 0;

    int mid=(l+r)>>1;

    int ans=0;

    if(a<=mid)
        ans+=query(a,b,l,mid,pos<<1);
    if(b>mid)
        ans+=query(a,b,mid+1,r,pos<<1|1);

    return ans;
}

void PushUp(int pos)
{
    t[pos]=t[pos<<1]+t[pos<<1|1];
}

void update(int p,int l,int r,int pos)
{
    if(l==r)
    {
        if(p==l)
            t[pos]++;
        return;
    }

    int mid=(l+r)>>1;

    if(p<=mid)
        update(p,l,mid,pos<<1);
    else
        update(p,mid+1,r,pos<<1|1);
    PushUp(pos);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int n;
    while(scanf("%d",&n)==1)
    {
        memset(t,0,sizeof(t));
        memset(level,0,sizeof(level));

        for(int i=0;i<n;i++)
        {
            int a,b;
            scanf("%d %d",&a,&b);
            level[query(0,a,0,MAX,1)]++;
            update(a,0,MAX,1);
        }
        for(int i=0;i<n;i++)
            printf("%d\n",level[i]);
    }

    return 0;
}
