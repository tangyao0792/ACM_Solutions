/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

using namespace std;

const int INF=1<<20;
int n;
int g[1010][1010],tax[1010],path[1010][1010];

void Floyd();
void outputPath(int cur, int dest);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d",&n)>0 && n)
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                scanf("%d",&g[i][j]);
                if(g[i][j]==-1)
                    g[i][j]=INF;
            }
        }
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&tax[i]);
        }
        Floyd();
        int x,y;
        while(scanf("%d %d",&x,&y)>0 && x!=-1&&y!=-1)
        {
            printf("From %d to %d :\n",x,y);
            printf("Path: ");
            outputPath(x,y);
            printf("\nTotal cost : %d\n\n",g[x][y]);

        }
    }
    return 0;
}
void outputPath(int u,int v)
{
    printf("%d",u);
    while(u!=v)
    {
        u=path[u][v];
        printf("-->%d",u);
    }
}
void Floyd()
{
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            path[i][j]=j;
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
            {
                if(i==k||j==k)  continue;
                int tmp=g[i][k]+g[k][j]+tax[k];
                if(g[i][j]>tmp)
                {
                    if(i!=k)
                    {
                        path[i][j]=path[i][k];
                        g[i][j]=tmp;
                    }
                }
                else if(g[i][j]==tmp && path[i][j]>path[i][k])
                {
                    path[i][j]=path[i][k];
                }
            }
}
