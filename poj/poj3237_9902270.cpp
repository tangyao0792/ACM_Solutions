#include<cstdio>
#include<cstring>

#define max(a,b) (a>b?a:b)

const int INF=1<<28;
const int MAXN=10010;
const int MAXM=2*MAXN;

struct edge
{
    int u,v,p,next;
}e[MAXM];

int first[MAXN],vis[MAXN],fa[MAXN],h[MAXN],w[MAXN];
int mx[MAXN];
int n,cnte;

void addedge(int x,int y,int p)
{
    e[cnte].u=x;e[cnte].v=y;e[cnte].p=p;
    e[cnte].next=first[x];
    first[x]=cnte++;

    e[cnte].u=y;e[cnte].v=x;e[cnte].p=p;
    e[cnte].next=first[y];
    first[y]=cnte++;
}

void dfs(int x,int cur)
{
    vis[x]=1;
    h[x]=cur;
    for(int i=first[x];i!=-1;i=e[i].next)
    {
        int v=e[i].v;
        if(vis[v]) continue;
        fa[v]=i;
        dfs(v,cur+1);
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase;
    scanf("%d",&nCase);

    const char* QUERY="QUERY";
    const char* CHANGE="CHANGE";
    const char* NEGATE="NEGATE";
    const char* DONE="DONE";
    char str[10];

    while(nCase--)
    {
        scanf("%d",&n);

        memset(first,-1,sizeof(first));
        memset(fa,-1,sizeof(fa));
        memset(vis,0,sizeof(vis));
        cnte=0;

        for(int i=1;i<n;i++)
        {
            int x,y,z;
            scanf("%d %d %d",&x,&y,&z);
            w[i]=z;
            addedge(x,y,i);
        }
        dfs(1,1);
        while(scanf("%s",str) && strcmp(DONE,str))
        {
            int x,y;
            scanf("%d %d",&x,&y);
            if(strcmp(CHANGE,str)==0)
            {
                w[x]=y;
            }
            else if(strcmp(NEGATE,str)==0)
            {
                while(h[x]<h[y])
                {
                    w[e[fa[y]].p]*=-1;
                    y=e[fa[y]].u;
                }
                while(h[x]>h[y])
                {
                    w[e[fa[x]].p]*=-1;
                    x=e[fa[x]].u;
                }
                while(x!=y)
                {
                    w[e[fa[y]].p]*=-1;
                    y=e[fa[y]].u;

                    w[e[fa[x]].p]*=-1;
                    x=e[fa[x]].u;
                }

            }
            else if(strcmp(QUERY,str)==0)
            {

                int ans=-INF;
                while(h[x]<h[y])
                {
                    ans=max(ans,w[e[fa[y]].p]);
                    y=e[fa[y]].u;
                }
                while(h[x]>h[y])
                {
                    ans=max(ans,w[e[fa[x]].p]);
                    x=e[fa[x]].u;
                }
                while(x!=y)
                {
                    ans=max(ans,w[e[fa[x]].p]);
                    x=e[fa[x]].u;
                    ans=max(ans,w[e[fa[y]].p]);
                    y=e[fa[y]].u;
                }
                printf("%d\n",ans);
            }
        }
    }
    return 0;
}
