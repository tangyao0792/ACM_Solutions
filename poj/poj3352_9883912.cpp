#include<cstdio>
#include<cstring>

#define min(a,b) (a<b?a:b)

const int MAXN=1010;

int g[MAXN][MAXN],f[MAXN][MAXN];
int id[MAXN],dfn[MAXN],low[MAXN],d[MAXN];
bool mark[MAXN];
int n,m,cnt,nscc,s[MAXN],sp,index;


void tarjan(int x,int flag)
{
    dfn[x]=low[x]=index++;
    s[sp++]=x;
    mark[x]=true;
    for(int y=1;y<=n;y++)
    {
        if(!g[x][y])    continue;
        g[y][x]=0;
        if(!dfn[y])
        {
            tarjan(y,flag);
            low[x]=min(low[x],low[y]);
            if(dfn[x]<low[y] && flag)
            {
                g[x][y]=g[y][x]=0;
            }
        }
        else if(mark[y])
        {
            low[x]=min(low[x],dfn[y]);
        }
    }
    if(dfn[x]==low[x])
    {
        int t;
        do
        {
            t=s[--sp];
            mark[t]=false;
            id[t]=nscc;
        }while(t!=x);
        nscc++;
    }
}

int solve()
{
    memset(mark,0,sizeof(mark));
    memset(dfn,0,sizeof(dfn));
    memset(id,0,sizeof(id));
    memcpy(f,g,sizeof(f));
    index=nscc=1;
    sp=0;
    for(int i=1;i<=n;i++)
        if(!dfn[i])
            tarjan(i,1);

    memset(d,0,sizeof(d));
    memset(mark,0,sizeof(mark));
    memset(dfn,0,sizeof(dfn));
    memset(id,0,sizeof(id));
    index=nscc=1;
    sp=0;

    for(int i=1;i<=n;i++)
        if(!dfn[i])
            tarjan(i,0);

    memset(g,0,sizeof(g));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(id[i]!=id[j] && f[i][j])
                g[id[i]][id[j]]=g[id[j]][id[i]]=1;

    for(int i=1;i<nscc;i++)
        for(int j=1;j<nscc;j++)
            if(g[i][j])
            {
                d[i]++;
                d[j]++;
            }

    int ans=0;
    for(int i=1;i<nscc;i++)
        if(d[i]==2)
            ans++;

    return (ans+1)/2;
}


int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d %d",&n,&m)==2)
    {
        memset(g,0,sizeof(g));
        cnt=0;
        for(int i=0;i<m;i++)
        {
            int x,y;
            scanf("%d %d",&x,&y);
            g[x][y]=g[y][x]=1;
        }
        printf("%d\n",solve());
    }
    return 0;
}
