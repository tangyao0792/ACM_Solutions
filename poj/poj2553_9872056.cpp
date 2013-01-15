#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

#define min(a,b) (a<b?a:b)

const int MAXN=5001;

bool g[MAXN][MAXN],vis[MAXN],ins[MAXN];
int dfn[MAXN],low[MAXN],s[MAXN],id[MAXN];
int n,m,index,sp,nscc;

void tarjan(int u)
{
    dfn[u]=low[u]=++index;
    s[sp++]=u;
    ins[u]=true;
    for(int i=1;i<=n;i++)
    {
        if(g[u][i] && !dfn[i])
        {
            tarjan(i);
            low[u]=min(low[u],low[i]);
        }
        else if(g[u][i] &&ins[i])
        {
            low[u]=min(low[u],dfn[i]);
        }
    }
    if(dfn[u]==low[u])
    {
        int t;
        do
        {
            t=s[--sp];
            id[t]=nscc;
            ins[t]=false;
        }while(t!=u);
        nscc++;
    }

}

void solve()
{
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(id,0,sizeof(id));
    memset(ins,0,sizeof(ins));

    sp=0;
    nscc=1;
    index=0;
    for(int i=1;i<=n;i++)
        if(!dfn[i])
            tarjan(i);

    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(g[i][j] && id[i]!=id[j])
                vis[id[i]]=true;
    sp=0;
    for(int i=1;i<nscc;i++)
        if(!vis[i])
            for(int j=1;j<=n;j++)
                if(id[j]==i)
                    s[sp++]=j;

    sort(s,s+sp);
    if(sp>0)
    {
        printf("%d",s[0]);
        for(int i=1;i<sp;i++)
            printf(" %d",s[i]);
    }
    printf("\n");
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d",&n)==1 && n)
    {
        memset(g,0,sizeof(g));
        scanf("%d",&m);
        for(int i=0;i<m;i++)
        {
            int x,y;
            scanf("%d %d",&x,&y);
            g[x][y]=true;
        }
        solve();
    }
    return 0;
}
