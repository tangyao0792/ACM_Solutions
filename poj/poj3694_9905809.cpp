#include<cstdio>
#include<cstring>

#define min(a,b) (a<b?a:b)

const int MAXN=100010;
const int MAXM=200010*2;

struct edge
{
    int u,v,id,next;
}e[MAXM];

int fe[MAXN];
int fa[MAXN];
int h[MAXN];
int dfn[MAXN],low[MAXN];
int vis[MAXN],vise[MAXM/2],visb[MAXM/2];
int n,m,cnte,cntb,nIndex,q;

void addedge(int x,int y,int i)
{
    e[cnte].u=x;e[cnte].v=y;e[cnte].id=i;
    e[cnte].next=fe[x];
    fe[x]=cnte++;
}

void tarjan(int u, int curh)
{
    dfn[u]=low[u]=nIndex++;
    h[u]=curh;
    vis[u]=1;
    for(int i=fe[u];i!=-1;i=e[i].next)
    {
        if(vise[e[i].id])   continue;
        vise[e[i].id]=1;
        int v=e[i].v;
        if(!vis[v])
        {
            fa[v]=i;
            tarjan(v,curh+1);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<low[v])
            {
                cntb++;
                visb[e[i].id]=1;
            }
        }
        else if(vis[v]==1)
        {
            low[u]=min(low[u],dfn[v]);
        }
    }
    vis[u]=2;
}

void swap(int &a,int &b)
{
    int tmp=a;
    a=b;
    b=tmp;
}

int solve(int x,int y)
{
    if(h[x]<h[y])
        swap(x,y);
    while(h[x]>h[y])
    {
        if(visb[e[fa[x]].id])
        {
            cntb--;
            visb[e[fa[x]].id]=0;
        }
        x=e[fa[x]].u;
    }
    while(x!=y)
    {
        if(visb[e[fa[x]].id])
        {
            cntb--;
            visb[e[fa[x]].id]=0;
        }
        x=e[fa[x]].u;
        if(visb[e[fa[y]].id])
        {
            cntb--;
            visb[e[fa[y]].id]=0;
        }
        y=e[fa[y]].u;
    }
    return cntb;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase=0;
    while(scanf("%d %d",&n,&m)==2 && !(!n && !m))
    {
        nCase++;
        memset(fe,-1,sizeof(fe));
        memset(vis,0,sizeof(vis));
        memset(vise,0,sizeof(vise));
        memset(visb,0,sizeof(visb));
        memset(fa,-1,sizeof(fa));
        nIndex=1;
        cnte=0;
        cntb=0;
        int x,y;
        for(int i=0;i<m;i++)
        {
            scanf("%d %d",&x,&y);
            addedge(x,y,i);addedge(y,x,i);
        }
        scanf("%d",&q);

        tarjan(1,0);
        printf("Case %d:\n",nCase);
        for(int i=0;i<q;i++)
        {
            scanf("%d %d",&x,&y);
            printf("%d\n",solve(x,y));
        }


//        for(int i=0;i<q;i++)
//            printf("%d\n",ans[i]);

        printf("\n");
    }
    return 0;
}
