#include<cstdio>
#include<cstring>

#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

const int MAXN=10010,MAXM=50010;

int u[MAXM],v[MAXM],next[MAXM];
int first[MAXN], id[MAXN],dfn[MAXN],low[MAXN];
bool mark[MAXN];
int index,nscc;
int s[MAXN],sp;
int n,m;

void tarjan(int u)
{
    dfn[u]=low[u]=index++;
    s[sp++]=u;
    mark[u]=true;
    for(int e=first[u];e!=-1;e=next[e])
    {
        if(!dfn[v[e]])
        {
            tarjan(v[e]);
            low[u]=min(low[u],low[v[e]]);
        }
        else if( mark[v[e]])
        {
            low[u]=min(low[u],dfn[v[e]]);
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

int solve()
{
    nscc=1;
    sp=0;
    index=1;
    for(int u=1;u<=n;u++)
        if(!dfn[u])
            tarjan(u);

    memset(mark,0,sizeof(mark));
    int p,f=0;
    for(int u=1;u<=n;u++)
        for(int e=first[u];e!=-1;e=next[e])
        {
            if(id[u]!=id[v[e]])
            {
                mark[id[u]]=true;   //出度不为0
            }
        }
    for(int u=1;u<nscc;u++)
        if(!mark[u])
        {
            f++;
            p=u;
            if(f>1)
                return 0;
        }
    int ans=0;
    for(int i=1;i<=n;i++)
        if(id[i]==p)
            ans++;
    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    scanf("%d %d", &n, &m);
    memset(first,-1,sizeof(first));
    memset(next,-1,sizeof(next));
    memset(dfn,0,sizeof(dfn));

    for(int i=0;i<m;i++)
    {
        scanf("%d %d",&u[i],&v[i]);
        next[i]=first[u[i]];
        first[u[i]]=i;
    }
    printf("%d\n",solve());
    return 0;
}
