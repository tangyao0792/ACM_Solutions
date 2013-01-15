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

const int MAXN=100010;

typedef long long LL;

struct Seg_Tree
{
    int left,right;
    int mid(){return (left+right)>>1;}
}t[MAXN*4];

int sorted[MAXN];
int toLeft[18][MAXN];        //how many ints in [l,i] are divided into left child
LL sumLeft[18][MAXN];
LL sum[MAXN];
int val[18][MAXN];
int n,m;
LL ans;

void build(int l,int r,int d,int pos)        //sorted must be done before
{
    t[pos].left=l;
    t[pos].right=r;
    if(l==r)
    {
        return;
    }
    int mid=t[pos].mid();
    int lsame=mid-l+1,lpos=l,rpos=mid+1;

    for(int i=l;i<=r;i++)
    {
        if(val[d][i]<sorted[mid])
            lsame--;
    }

    for(int i=l;i<=r;i++)
    {
        if(i==l)
        {
            toLeft[d][i]=0;
            sumLeft[d][i]=0;
        }
        else
        {
            toLeft[d][i]=toLeft[d][i-1];
            sumLeft[d][i]=sumLeft[d][i-1];
        }
        if(val[d][i]<sorted[mid])
        {
            val[d+1][lpos++]=val[d][i];
            toLeft[d][i]++;
            sumLeft[d][i]+=val[d][i];
        }
        else if(val[d][i]>sorted[mid])
        {
            val[d+1][rpos++]=val[d][i];
        }
        else
        {
            if(lsame>0)
            {
                lsame--;
                val[d+1][lpos++]=val[d][i];
                toLeft[d][i]++;
                sumLeft[d][i]+=val[d][i];
            }
            else
            {
                val[d+1][rpos++]=val[d][i];
            }
        }
    }
    build(l,mid,d+1,pos<<1);
    build(mid+1,r,d+1,pos<<1|1);
}

int find(int l,int r,int k,int d,int pos)       // the kth small number
{
    if(l==r)
    {
        ans+=val[d][l];
        return val[d][l];
    }
    int s,ss;            //ss is number of ints in [t[pos].left, l-1] divided into left child
                        //s         [l,r]
    LL tmp;
    if(l==t[pos].left)
    {
        ss=0;
        tmp=sumLeft[d][r];
    }
    else
    {
        ss=toLeft[d][l-1];
        tmp=sumLeft[d][r]-sumLeft[d][l-1];
    }

    s=toLeft[d][r]-ss;

    if(s>=k)            //next left child
    {
        int newl=t[pos].left+ss;
        int newr=t[pos].left+s+ss-1;
        return find(newl,newr,k,d+1,pos<<1);
    }
    else
    {
        int b=l-t[pos].left-ss;        //number of [t[pos].left,l-1] into right child
        int bb=r - l + 1 - s;                        //            [l,r]
        int mid=t[pos].mid();
        int newl=mid+b+1;
        int newr=mid+b+bb;
        ans+=tmp;
        return find(newl,newr,k-s,d+1,pos<<1|1);
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    int T;
    scanf("%d",&T);
    int nCase=0;
    while(T--)
    {
        nCase++;
        scanf("%d",&n);
        sum[0]=sum[1]=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&sorted[i]);
            sum[i]=sum[i-1]+sorted[i];
            val[0][i]=sorted[i];
        }
        sort(sorted+1,sorted+n+1);
        build(1,n,0,1);

        scanf("%d",&m);

        printf("Case #%d:\n",nCase);
        while(m--)
        {
            int l,r,k;
            scanf("%d %d",&l,&r);
            l++,r++;
            k=(r-l)/2+1;
            ans=0;
            LL kth=find(l,r,k,0,1);
            LL tmp=(LL)k*kth-ans + sum[r]-sum[l-1]-ans-(LL)(r-l+1-k)*kth;
            printf("%I64d\n",tmp);
        }
        puts("");
    }
    return 0;
}
