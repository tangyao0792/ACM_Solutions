#include<cstdio>
#include<cstring>

#define max(a,b) (a>b?a:b)

const int INF=1<<28;
const int MAXN=110;

int g[MAXN][MAXN],lowc[MAXN],v[MAXN],f[MAXN][MAXN],fa[MAXN];
int vis[MAXN][MAXN];
int n,m;

int prim()
{
    for(int i=1;i<=n;i++)
    {
        lowc[i]=g[1][i];
        fa[i]=1;
    }
    memset(vis,0,sizeof(vis));
    memset(f,0,sizeof(f));
    memset(v,0,sizeof(v));
    v[1]=1;
    int ans=0;
    int mind,minn;

    for(int i=0;i<n-1;i++)
    {
        mind=INF;
        for(int j=1;j<=n;j++)
        {
            if(!v[j] && lowc[j]<mind)
            {
                minn=j;
                mind=lowc[j];
            }
        }
        ans+=mind;
        for(int j=1;j<=n;j++)
        {
            if(v[j])
            {
                f[j][minn]
                =f[minn][j]
                =max(f[j][fa[minn]],g[minn][fa[minn]]);
            }
        }
        vis[fa[minn]][minn]=vis[minn][fa[minn]]=1;
        v[minn]=1;

        for(int j=1;j<=n;j++)
        {
            if(!v[j] && g[j][minn]<lowc[j])
            {
                lowc[j]=g[j][minn];
                fa[j]=minn;
            }
        }

    }

    return ans;
}

void output()
{
    int ans=prim();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(!vis[i][j] && g[i][j]<INF && f[i][j]==g[i][j])
            {
                printf("Not Unique!\n");
                return;
            }
    printf("%d\n",ans);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase;
    scanf("%d", &nCase);
    while(nCase--)
    {
        scanf("%d %d", &n, &m);

        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                g[i][j]=INF;

        for(int i=0;i<m;i++)
        {
            int x,y,z;
            scanf("%d %d %d",&x,&y,&z);
            g[x][y]=g[y][x]=z;
        }
        output();
    }
    return 0;
}
