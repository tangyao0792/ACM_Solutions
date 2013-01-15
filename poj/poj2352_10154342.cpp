#include<cstdio>
#include<cstring>

#define max(a,b) (a>b?a:b)

const int MAXN=32010;

int in[MAXN];
int level[MAXN];
int n,m;

int lowbit(int t)
{
    return t&(t^(t-1));
}

void plus(int pos)
{
    while(pos<=m)
    {
        in[pos]++;
        pos+=lowbit(pos);
    }
}

int getsum(int k)
{
    int ans=0;
    while(k>0)
    {
        ans+=in[k];
        k-=lowbit(k);
    }
    return ans;
}


int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r",stdin);
#endif

    scanf("%d",&n);
    m=MAXN;
    for(int i=0;i<n;i++)
    {
        int x,y;
        scanf("%d %d",&x,&y);
        x++;
        level[getsum(x)]++;
        plus(x);
    }
    for(int i=0;i<n;i++)
        printf("%d\n",level[i]);

    return 0;
}
