#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;

const int MAXN=100100;
const int MAXM=2*MAXN;

int in[MAXN];           //新编号下的数组
int treearray[MAXN];
int pos[MAXN];          //pos[i]表示，i号节点的编号
int num[MAXN];          //num[pos[i]]:i节点的孩子数
int first[MAXN],next[MAXM],v[MAXM];
int n,cnt,q,nIndex;

inline void addedge(int x,int y)
{
    v[cnt]=y;
    next[cnt]=first[x];
    first[x]=cnt++;
}

int dfs(int root,int fa)
{
    int ans=0;
    for(int e=first[root];e!=-1;e=next[e])
    {
        if(v[e]==fa)    continue;

        ans+=dfs(v[e],root);
    }

    pos[root]=nIndex++;
    num[pos[root]]=ans;
    return ans+1;
}

inline int lowbit(int x)
{
    return x&(x^(x-1));
}

void update(int p)
{
    int tmp;
    if(in[p]==1)
        tmp=-1;
    else
        tmp=1;
    in[p]^=1;

    while(p<=n)
    {
        treearray[p]+=tmp;
        p+=lowbit(p);
    }
}
int getsum(int p)
{
    int ans=0;
    while(p>0)
    {
        ans+=treearray[p];
        p-=lowbit(p);
    }
    return ans;
}
int get(int l,int r)
{
    return getsum(r)-getsum(l-1);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r",stdin);
#endif

    while(scanf("%d",&n)==1 && n)
    {
        cnt=0;
        nIndex=1;
        memset(first,-1,sizeof(first));
        memset(in,0,sizeof(in));
        memset(treearray,0,sizeof(treearray));

        for(int i=1;i<n;i++)
        {
            int x, y;
            scanf("%d %d",&x,&y);
            addedge(x,y);
            addedge(y,x);
        }

        dfs(1,-1);

        for(int i=1;i<=n;i++)
            update(pos[i]);

        int q;
        scanf("%d\n",&q);
        for(int i=0;i<q;i++)
        {
            char c;int t;
            scanf("%c %d\n",&c,&t);
            if(c=='C')
                update(pos[t]);
            else
                printf("%d\n",get(pos[t]-num[pos[t]],pos[t]));
        }
    }

    return 0;
}
