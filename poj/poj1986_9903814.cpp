#include<cstdio>
#include<cstring>

#define max(a,b) (a>b?a:b)

const int MAXN=40010;
const int MAXM=2*MAXN;
const int MAXQ=20010;

struct edge
{
    int u,v,w,next;
}e[MAXM];
struct quest
{
    int u,v,ans,next,p;
}que[MAXQ];
struct newquest
{
    int p,next;
}nq[MAXQ];

int fe[MAXN],fq[MAXN],p[MAXN],dis[MAXN],vis[MAXN],fnq[MAXN];
int n,m,cnte,cntq,q,cntnq;

void addedge(int x,int y,int z)
{
    e[cnte].u=x;e[cnte].v=y;e[cnte].w=z;
    e[cnte].next=fe[x];
    fe[x]=cnte++;
    e[cnte].u=y;e[cnte].v=x;e[cnte].w=z;
    e[cnte].next=fe[y];
    fe[y]=cnte++;
}
void addq(int x,int y, int i)
{
    que[cntq].p=i;
    que[cntq].u=x;que[cntq].v=y;
    que[cntq].next=fq[x];
    fq[x]=cntq++;
    que[cntq].p=i;
    que[cntq].u=y;que[cntq].v=x;
    que[cntq].next=fq[y];
    fq[y]=cntq++;
}
void addnq(int x,int p)
{
    nq[cntnq].p=p;
    nq[cntnq].next=fnq[x];
    fnq[x]=cntnq++;
}
int find(int x){return p[x]==x?x:(p[x]=find(p[x]));}
void unionset(int x,int y)
{
    int px=find(x);
    int py=find(y);
    p[px]=p[py];
}
void lca(int par,int fa, int d)
{
    p[par]=par;
    dis[par]=d;
    vis[par]=1;
    for(int i=fq[par];i!=-1;i=que[i].next)
    {
        int v=que[i].v;
        if(vis[v])
            addnq(find(v),i);
            //==addnq(fa,i);
    }
    for(int i=fe[par];i!=-1;i=e[i].next)
    {
        int v=e[i].v;
        if(v==fa)   continue;
        lca(v,par,d+e[i].w);
        unionset(v,par);
    }

    for(int i=fnq[par];i!=-1;i=nq[i].next)
    {
        int p=nq[i].p;
        int x=que[p].u;
        int y=que[p].v;
        que[que[p].p].ans=dis[x]+dis[y]-2*d;
    }
}
inline void readint(int &ret)
{
	char c;
	do {	c = getchar();
	} while(c < '0' || c > '9');
	ret = c - '0';
	while((c=getchar()) >= '0' && c <= '9')
		ret = ret * 10 + ( c - '0' );
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d %d",&n,&m)==2)
    {
        cnte=cntq=cntnq=0;
        memset(fe,-1,sizeof(fe));
        memset(vis,0,sizeof(vis));
        memset(fnq,-1,sizeof(fnq));
        memset(fq,-1,sizeof(fq));
        for(int i=0;i<m;i++)
        {
            int x,y,z;char c;
//            scanf("%d %d %d %c",&x,&y,&z,&c);
            readint(x);readint(y);readint(z);
            c=getchar();
            addedge(x,y,z);
        }
        scanf("%d",&q);
        for(int i=0;i<q;i++)
        {
            int x,y;
//            scanf("%d %d",&x,&y);
            readint(x);readint(y);
            addq(x,y,i);

        }
        lca(1,-1,0);
        for(int i=0;i<q;i++)
            printf("%d\n",que[i].ans);
    }
    return 0;
}
