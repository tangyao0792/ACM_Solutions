/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

#define min(a,b) (a<b?a:b)

const int MAXN=5010;

int v[4*MAXN];
int a[MAXN];

int update(int p,int l,int r,int pos)
{
    if(l==p && r==p)
    {
        return v[pos]=1;
    }

    int mid=(l+r)>>1;

    if(p<=mid)
        v[pos]+=update(p,l,mid,pos<<1);
    if(p>mid)
        v[pos]+=update(p,mid+1,r,pos<<1|1);

    return 1;
}

int query(int a,int b,int l,int r,int pos)
{
    if(a==l && b==r)
    {
        return v[pos];
    }
    if(l==r)    return 0;
    int mid=(l+r)>>1;


    if(b<=mid)
        return query(a,b,l,mid,pos<<1);
    else if(a>mid)
        return query(a,b,mid+1,r,pos<<1|1);
    else
        return query(a,mid,l,mid,pos<<1)+query(mid+1,b,mid+1,r,pos<<1|1);

}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int n;
    while(scanf("%d",&n)==1)
    {
        memset(v,0,sizeof(v));
        int ans=0;
        for(int i=0;i<n;i++)
        {
            scanf("%d",&a[i]);
            ans+=query(a[i],n-1,0,n-1,1);
            update(a[i],0,n-1,1);
        }
        int nMin=ans;
        for(int i=0;i<n;i++)
        {
            ans=ans-a[i]+n-a[i]-1;
            nMin=min(ans,nMin);
        }
        printf("%d\n",nMin);
    }
    return 0;
}
