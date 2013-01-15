#include<cstdio>
#include<cstring>

const int MAXN=8010;

int order[MAXN],s[MAXN],sp;
int n;
struct TNode
{
    int left,right,n;
}T[2*MAXN];

void build(int s,int t,int step)
{
    T[step].left=s;
    T[step].right=t;
    T[step].n=t-s+1;

    if(s==t)    return;

    int mid=(s+t)/2;
    build(s,mid,step*2);
    build(mid+1,t,step*2+1);
}

int find(int step,int target)
{
    T[step].n--;

    if(T[step].left==T[step].right)
        return T[step].right;
    else if(T[step*2].n>=target)
        return find(step*2,target);
    else
        return find(step*2+1,target-T[step*2].n);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d",&n)==1)
    {
        order[1]=0;
        for(int i=2;i<=n;i++)
            scanf("%d",&order[i]);

        build(1,n,1);
        sp=0;
        for(int i=n;i>=1;i--)
            s[sp++]=find(1,order[i]+1);

        for(int i=sp-1;i>=0;i--)
            printf("%d\n",s[i]);
    }
    return 0;
}
