/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<iostream>
#include<cstring>

using namespace std;

const int MAXN=510;
int g[MAXN][MAXN],topo[MAXN],d[MAXN];
int n,m;

void toposort()
{
    for(int i=0;i<n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(d[j]==0)
            {
                d[j]=-1;
                topo[i]=j;
                for(int k=1;k<=n;k++)
                {
                    if(g[j][k])
                        d[k]--;
                }
                break;
            }
        }
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    while(scanf("%d %d",&n,&m)==2)
    {
        memset(d,0,sizeof(d));
        memset(g,0,sizeof(g));
        for(int i=0;i<m;i++)
        {
            int x,y;
            scanf("%d %d",&x,&y);
            if(!g[x][y])
            {
                g[x][y]=1;
                d[y]++;
            }
        }
        toposort();
        printf("%d",topo[0]);
        for(int i=1;i<n;i++)
            printf(" %d",topo[i]);
        printf("\n");
    }

}
