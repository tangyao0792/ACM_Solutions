#include<cstdio>
#include<cstring>

const int MAXN=1050;

int treeArray[MAXN][MAXN];
int n;

inline int lowbit(int x)
{
    return x&(x^(x-1));
}

void add(int x,int y,int a)
{
    for(int i=x;i<=n;i+=lowbit(i))
    {
        for(int j=y;j<=n;j+=lowbit(j))
        {
            treeArray[i][j]+=a;
        }
    }
}

int getsum(int x,int y)
{
    int ans=0;
    for(int i=x;i>0;i-=lowbit(i))
    {
        for(int j=y;j>0;j-=lowbit(j))
        {
            ans+=treeArray[i][j];
        }
    }
    return ans;
}

int query(int l,int b,int r,int t)
{
    return getsum(r,t)+getsum(l-1,b-1)-getsum(r,b-1)-getsum(l-1,t);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r",stdin);
#endif

    int ins;
    while(scanf("%d",&ins)==1 && ins!=3)
    {
        if(ins==0)
            scanf("%d",&n);
        else if(ins==1)
        {
            int x,y,a;
            scanf("%d %d %d",&x,&y,&a);
            x++;y++;
            add(x,y,a);
        }
        else
        {
            int l,b,r,t;
            scanf("%d %d %d %d",&l,&b,&r,&t);
            printf("%d\n",query(l+1,b+1,r+1,t+1));
        }
    }

    return 0;
}
