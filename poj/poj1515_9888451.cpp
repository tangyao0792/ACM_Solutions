#include<cstdio>
#include<cstring>

#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

const int MAXN=1010;
const int MAXM=MAXN*8;

int first[MAXN],dfn[MAXN],low[MAXN],vis[MAXN];
int next[MAXM],u[MAXM],v[MAXM],mark[MAXM];
int n,m,nIndex,cnt;

void addedge(int x, int y)
{
    u[cnt]=x;
    v[cnt]=y;
    next[cnt]=first[x];
    first[x]=cnt++;
}

void tarjan(int x,int fa)
{
    dfn[x]=low[x]=nIndex++;
    vis[x]=1;
    for(int e=first[x];e!=-1;e=next[e])
    {

        int y=v[e];
        if(y==fa)   continue;

        if(vis[y] != 2) mark[e]=true;
        if(!vis[y])
        {
            tarjan(y,x);
            low[x]=min(low[x],low[y]);
            if(dfn[x]<low[y])
                mark[e]=false;
        }
        else if(vis[y]==1)
        {
            low[x]=min(low[x],dfn[y]);
        }
    }
    vis[x]=2;
}

void solve()
{
    memset(vis,0,sizeof(vis));
    memset(mark,0,sizeof(mark));
    nIndex=1;
    for(int i=1;i<=n;i++)
        if(!vis[i])
            tarjan(i, -1);

    for(int i=1;i<=n;i++)
        for(int e=first[i]; e!=-1; e=next[e])
            if(!mark[e])
                printf("%d %d\n",u[e],v[e]);

}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase=0;
    while(scanf("%d %d",&n,&m)==2 && !(!n && !m))
    {
        memset(first,-1,sizeof(first));
        cnt=0;
        for(int i=0;i<m;i++)
        {
            int x,y;
            scanf("%d %d",&x,&y);
            addedge(x,y);
            addedge(y,x);
        }
        nCase++;
        printf("%d\n\n",nCase);
        solve();
        printf("#\n");
    }
    return 0;
}
