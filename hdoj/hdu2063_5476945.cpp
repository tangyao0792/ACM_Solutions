/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

const int MAXN=510;

int g[MAXN][MAXN],xM[MAXN],yM[MAXN];
bool chk[MAXN];
int n,m,k;

bool SearchPath(int u)
{
    for(int v=1;v<=m;v++)
        if(g[u][v] && !chk[v])
        {
            chk[v]=true;
            if(yM[v]==-1 || SearchPath(yM[v]))
            {
                yM[v]=u;
                xM[u]=v;
                return true;
            }
        }

    return false;
}

int MaxMatch()
{
    int ans=0;
    memset(xM,-1,sizeof(xM));
    memset(yM,-1,sizeof(yM));
    for(int i=1;i<=n;i++)
        if(xM[i]==-1)
        {
            memset(chk,0,sizeof(chk));
            if(SearchPath(i))   ans++;
        }

    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d",&k)==1 && k)
    {
        scanf("%d %d",&n,&m);
        memset(g,0,sizeof(g));
        for(int i=0;i<k;i++)
        {
            int x,y;
            scanf("%d %d",&x,&y);
            g[x][y]=1;
        }
        printf("%d\n",MaxMatch());
    }
    return 0;
}
