#include<cstdio>
#include<cstring>

const int INF = 1<<28;
int g[1010][1010];
int v[1010], d[1010];
int n, m;
int nMax;

int min(int a, int b){return a<b?a:b;}
int max(int a, int b){return a>b?a:b;}

void Dijkstra();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase, iCase;
    scanf("%d", &nCase);
    for(iCase = 1; iCase <= nCase; iCase++)
    {
        memset(g, 0, sizeof(g));
        printf("Scenario #%d:\n",iCase);
        scanf("%d %d",&n, &m);
        for(int i = 1; i <= m; i++)
        {
            int x, y, w;
            scanf("%d %d %d",&x,&y,&w);
            g[x][y]=g[y][x]=w;
        }
        Dijkstra();
        printf("%d\n\n",d[n]);
    }
    return 0;
}

void Dijkstra()
{
    memset(v, 0, sizeof(v));
    for(int i = 0; i <=n;i++)g[i][i]=INF;
    for(int i = 1; i<=n;i++)
    {
        d[i]=g[1][i];
    }
    for(int i = 0; i < n; i++)
    {
        int x, m = 0;
        for(int y = 1; y<=n;y++)
        {
            if(!v[y] && d[y]>=m)
                m = d[x=y];
        }
        v[x]=1;
        for(int y = 1; y<=n;y++)
        {
            if( !v[y]&&d[y]<min(d[x],g[x][y]))
            {
                d[y] = min(d[x],g[x][y]);
            }
        }
    }
}
