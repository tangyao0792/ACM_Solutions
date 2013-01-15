#include<cstdio>
#include<cstring>

const int INF = 1<<28;
int n, m, q;
int d[110][110];

int max(int a,int b){return a>b?a:b;}
int min(int a,int b){return a<b?a:b;}
void Floyd();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    int nCase = 0;
    while(scanf("%d %d %d", &n,&m,&q)>0 && n)
    {
        if(nCase)   printf("\n");
        for(int i=0;i<110;i++)
            for(int j=0;j<110;j++)
            {
                d[i][j]=INF;
            }
        nCase++;
        for(int i=0;i<m;i++)
        {
            int x, y, w;
            scanf("%d %d %d",&x,&y,&w);
            d[x][y]=d[y][x]=w;
        }
        Floyd();
        printf("Case #%d\n",nCase);
        for(int i=0;i<q;i++)
        {
            int x,y;
            scanf("%d %d",&x,&y);
            if(d[x][y]==INF)    printf("no path\n");
            else    printf("%d\n",d[x][y]);
        }
    }
    return 0;
}

void Floyd()
{
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
            {
                if(d[i][k]<INF && d[k][j]<INF)
                {
                    d[i][j]=min(d[i][j],max(d[i][k],d[k][j]));
                }
            }
}
