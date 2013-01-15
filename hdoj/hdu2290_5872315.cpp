/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;

const long long INF = 40000000;
const int MAXN=210;

typedef int ll;

struct point
{
    int id,w;
}p[1100];

int pos[1100];
ll g[MAXN][MAXN][MAXN];
int n,m;

bool comp(point x,point y)
{
    return x.w<y.w;
}

void floyd()
{
    for(int k=1;k<=n;k++)
    {
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                g[i][j][k]=g[i][j][k-1];

        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                if(g[i][j][k]>g[i][k][k-1]+g[k][j][k-1])
                    g[i][j][k]=g[i][k][k-1]+g[k][j][k-1];
    }

}


int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif

    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %d",&n,&m);
        for(int i=0;i<n;i++)
        {
            scanf("%d",&p[i].w);
            p[i].id=i;
        }

        sort(p,p+n,comp);

        for(int i=0;i<n;i++)
            pos[p[i].id]=i+1;

        for(int k=0;k<MAXN;k++)
            for(int i=0;i<MAXN;i++)
            {
                for(int j=0;j<MAXN;j++)
                    g[i][j][k]=INF;
                g[i][i][k]=0;
            }

        for(int i=0;i<m;i++)
        {
            int x,y,w;
            scanf("%d %d %d",&x,&y,&w);
            g[pos[x]][pos[y]][0]=g[pos[y]][pos[x]][0]=
                min(g[pos[y]][pos[x]][0],w);
        }

        floyd();

        int q;
        scanf("%d",&q);
        for(int i=0;i<q;i++)
        {
            int x,y,w;
            scanf("%d %d %d",&x,&y,&w);

            int ans=INF;
            ans=min(ans,g[pos[x]][pos[y]][0]);
            for(int j=n-1;j>=0;j--)
                if(p[j].w<=w)
                {
                    ans=min(ans,g[pos[x]][pos[y]][j+1]);
                    break;
                }

            if(ans<INF)
                printf("%d\n",ans);
            else
                printf("-1\n");
        }
        printf("\n");
    }

    return 0;
}
