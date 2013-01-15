#include<cstdio>
#include<cstring>

#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)

const int MAXN=110;

int g[MAXN][MAXN],dfn[MAXN],low[MAXN],id[MAXN];
bool mark[MAXN];
int s[MAXN],sp,in[MAXN],out[MAXN];
int n,nscc,index;

void tarjan(int u)
{
    dfn[u]=low[u]=index++;
    s[sp++]=u;
    mark[u]=true;
    for(int v=1;v<=n;v++)
    {
        if(g[u][v])
        {
            if(!dfn[v])
            {
                tarjan(v);
                low[u]=min(low[u],low[v]);
            }
            else if( mark[v])
            {
                low[u]=min(low[u],dfn[v]);
            }
        }
    }
    if(dfn[u]==low[u])
    {
        int t;
        do
        {
            t=s[--sp];
            id[t]=nscc;
            mark[t]=false;
        }while(t!=u);
        nscc++;
    }
}

void solve()
{
    index=1;
    nscc=0;
    sp=0;
    memset(mark,0,sizeof(mark));
    memset(id,0,sizeof(id));

    for(int i=1;i<=n;i++)
        if(!dfn[i])
            tarjan(i);

    memset(mark,0,sizeof(mark));
    memset(in,0,sizeof(in));
    memset(out,0,sizeof(out));

    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(g[i][j] && id[i]!=id[j])
            {
                in[id[j]]++;
                out[id[i]]++;
            }

    int nIn=0,nOut=0;
    for(int i=0;i<nscc;i++)
        if(!in[i])
            nIn++;
        else if(!out[i])
            nOut++;


    printf("%d\n",nIn);
    int ans=max(nIn,nOut);
    if(nscc==1)
        ans=0;
    printf("%d\n",ans);

}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif

    while(scanf("%d",&n)==1)
    {
        memset(g,0,sizeof(g));
        for(int i=1;i<=n;i++)
        {
            int x;
            while(scanf("%d",&x)==1 && x)
                g[i][x]=1;
        }
        solve();
    }
    return 0;
}
