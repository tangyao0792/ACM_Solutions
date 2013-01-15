#include<cstdio>
#include<cstring>

#define min(a,b) (a<b?a:b)

const int MAXN=100010;
const int MAXM=200010*2;

struct edge
{
    int u,v,id,next;
}e[MAXM];

int f[MAXN];
int out[MAXM/2];        //记录一条边是否被删
int n,m,cnt;
int cntb;               //桥数
int dfn[MAXN],low[MAXN];
int id[MAXN],nIndex;
int vise[MAXM];         //边是否访问过
int vis[MAXN];
int fa[MAXN];           //树
int isb[MAXN];          //记录数边是否为桥
int h[MAXN];

void addedge(int x,int y,int id)
{
    e[cnt].u=x;e[cnt].v=y;e[cnt].id=id;
    e[cnt].next=f[x];
    f[x]=cnt++;
}
void tarjan(int u)
{
    dfn[u]=low[u]=nIndex++;
    vis[u]=1;
    for(int i=f[u];i!=-1;i=e[i].next)
    {
        if(vise[e[i].id])   continue;
        vise[e[i].id]=1;
        int v=e[i].v;
        if(!vis[v])
        {
            tarjan(v);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<low[v])
            {
                cntb++;
                out[e[i].id]=1;
            }
        }
        else if(vis[v]==1)
        {
            low[u]=min(low[u],dfn[v]);
        }
    }
    vis[u]=2;
}

void dfs(int u)
{
    id[u]=nIndex;
    for(int i=f[u];i!=-1;i=e[i].next)
    {
        if(!out[e[i].id] && !id[e[i].v])
        {
            dfs(e[i].v);
        }
    }
}

void buildtree(int u,int ch)
{
    h[id[u]]=ch;
    vis[u]=1;
    for(int i=f[u];i!=-1;i=e[i].next)
    {
        int v=e[i].v;
        if(!vis[v])
        {
            if(id[u]==id[v])
            {
                buildtree(v,ch);
            }
            else
            {
                fa[id[v]]=id[u];
                if(out[e[i].id])
                    isb[id[v]]=1;
                buildtree(v,ch+1);
            }
        }
    }
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
        if(isb[x])
        {
            cntb--;
            isb[x]=0;
        }
        x=fa[x];
    }
    while(x!=y)
    {
        if(isb[x])
        {
            cntb--;
            isb[x]=0;
        }
        x=fa[x];
        if(isb[y])
        {
            cntb--;
            isb[y]=0;
        }
        y=fa[y];
    }
    return cntb;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase=0;
    while(scanf("%d %d",&n,&m)==2)
    {
        if(n==0 && m==0)    break;
        nCase++;
        cnt=cntb=0;
        memset(out,0,sizeof(out));
        memset(vise,0,sizeof(vise));
        memset(f,-1,sizeof(f));
        memset(vis,0,sizeof(vis));
        memset(id,0,sizeof(id));
        memset(fa,-1,sizeof(fa));
        memset(isb,0,sizeof(isb));
        memset(h,0,sizeof(h));
        nIndex=1;
        for(int i=0;i<m;i++)
        {
            int x,y;
            scanf("%d %d",&x,&y);
            addedge(x,y,i);addedge(y,x,i);
        }
        tarjan(1);
        nIndex=1;
        for(int i=1;i<=n;i++)       //缩点
        {
            if(!id[i])
            {
                dfs(i);
                nIndex++;
            }
        }
        memset(vis,0,sizeof(vis));
        buildtree(1,0);

        int q;
        scanf("%d",&q);
        printf("Case %d:\n",nCase);
        for(int i=0;i<q;i++)
        {
            int x,y;
            scanf("%d %d",&x,&y);
            printf("%d\n",solve(id[x],id[y]));
        }
        printf("\n");
    }
    return 0;
}
