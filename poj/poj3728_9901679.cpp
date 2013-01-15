#include<cstdio>
#include<cstring>

#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

const int MAXN=50010;
const int MAXM=2*MAXN;

struct edge
{
    int u,v,next;
}e[MAXM];
struct quest
{
    int u,v,id,next,ans;
}que[MAXM];
struct newquest
{
    int p,next;
}nq[MAXM];

int mx[MAXN],mn[MAXN],up[MAXN],dw[MAXN];
int fe[MAXN],fq[MAXN],fnq[MAXN];
int ans[MAXM],p[MAXN],vis[MAXN];
int n,q,cnte,cntq,cntnq;

void addq(int x,int y, int p)
{
    que[cntq].ans=p;
    que[cntq].u=x;que[cntq].v=y;
    que[cntq].id=1;
    que[cntq].next=fq[x];
    fq[x]=cntq++;
    que[cntq].ans=p;
    que[cntq].u=y;que[cntq].v=x;
    que[cntq].id=-1;
    que[cntq].next=fq[y];
    fq[y]=cntq++;
}
void addedge(int x, int y)
{
    e[cnte].u=x;e[cnte].v=y;
    e[cnte].next=fe[x];
    fe[x]=cnte++;
    e[cnte].v=x;e[cnte].u=y;
    e[cnte].next=fe[y];
    fe[y]=cnte++;
}

void addnq(int x, int p)
{
    nq[cntnq].p=p;
    nq[cntnq].next=fnq[x];
    fnq[x]=cntnq++;
}

void swap(int &x,int &y)
{
    int tmp=x;
    x=y;
    y=tmp;
}

int find(int x)
{
    if(p[x]==x) return x;
    int y=p[x];
    p[x]=find(p[x]);
    up[x]=max(mx[y]-mn[x],max(up[x],up[y]));
    dw[x]=max(mx[x]-mn[y],max(dw[x],dw[y]));
    mx[x]=max(mx[x],mx[y]);
    mn[x]=min(mn[x],mn[y]);
    return p[x];
}

void unionp(int x,int y)
{
    int px=find(x);
    int py=find(y);
    p[px]=py;
}

void lca(int par, int fa)
{

    p[par]=par;
    for(int i=fq[par];i!=-1;i=que[i].next)
    {
        int v=que[i].v;
        if(vis[v])
        {
            addnq(find(v),i);
        }
    }
        vis[par]=1;
    for(int i=fe[par];i!=-1;i=e[i].next)
    {
        int y=e[i].v;
        if(y==fa)   continue;
        lca(y,par);
        unionp(y,par);
    }


    for(int i=fnq[par];i!=-1;i=nq[i].next)
    {
        int pe=nq[i].p;
        int from=que[pe].u;
        int to=que[pe].v;
        find(from);
        find(to);
        if(que[pe].id ==-1)
            swap(from,to);
        ans[que[pe].ans]=max(mx[to]-mn[from],max(up[from],dw[to]));
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    scanf("%d",&n);
    {
        memset(fe,-1,sizeof(fe));
        memset(fq,-1,sizeof(fq));
        memset(fnq,-1,sizeof(fnq));
        memset(vis,0,sizeof(vis));
        cnte=cntq=cntnq=0;
        for(int i=1;i<=n;i++)
        {
            int tmp;scanf("%d",&tmp);
            mx[i]=mn[i]=tmp;
            up[i]=dw[i]=0;
        }
        for(int i=1;i<n;i++)
        {
            int x,y;
            scanf("%d %d",&x,&y);
            addedge(x,y);
        }
        scanf("%d",&q);
        for(int i=0;i<q;i++)
        {
            int x,y;
            scanf("%d %d",&x,&y);
            addq(x,y,i);
        }
        lca(1,-1);
        for(int i=0;i<q;i++)
            printf("%d\n",ans[i]);
    }
    return 0;
}
