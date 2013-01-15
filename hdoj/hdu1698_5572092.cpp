/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

const int MAXN=100100;

int n,q;

struct Tree
{
    int l,r,c;
}T[MAXN*5];

void build(int s,int t,int pos)
{
    T[pos].l=s;
    T[pos].r=t;
    T[pos].c=1;

    if(s==t)    return;

    int mid=(s+t)>>1;

    build(s,mid,pos*2);
    build(mid+1,t,pos*2+1);
}

void ins(int s,int t,int id,int pos)
{
    if(s==T[pos].l && t==T[pos].r)
    {
        T[pos].c=id;
        return;
    }
    if(T[pos].c != 0)
    {
        T[pos*2].c=T[pos].c;
        T[pos*2+1].c=T[pos].c;
        T[pos].c=0;
    }
    int l=T[pos].l;
    int r=T[pos].r;

    int mid=(l+r)>>1;

    if(mid>=t)
    {
        ins(s,t,id,2*pos);
    }
    else if(mid<s)
    {
        ins(s,t,id,2*pos+1);
    }
    else
    {
        ins(s,mid,id,pos*2);
        ins(mid+1,t,id,pos*2+1);
    }
}
int find(int pos)
{
    if(T[pos].c!=0)
    {
        return T[pos].c*(T[pos].r-T[pos].l+1);
    }
    return find(pos*2)+find(pos*2+1);
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase;
    scanf("%d",&nCase);
    for(int iCase=1;iCase<=nCase;iCase++)
    {
        scanf("%d",&n);
        build(1,n,1);
        scanf("%d",&q);

        for(int i=0;i<q;i++)
        {
            int x,y,z;
            scanf("%d %d %d",&x,&y,&z);
            ins(x,y,z,1);
        }
        printf("Case %d: The total value of the hook is %d.\n",iCase,find(1));
    }
    return 0;
}
