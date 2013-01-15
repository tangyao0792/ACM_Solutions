/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

const int MAXN=510;

int g[MAXN][MAXN],xM[MAXN],yM[MAXN],chk[MAXN];
int n;

bool dfs(int u)
{
    for(int v=0;v<n;v++)
    {
        if(g[u][v] && !chk[v])
        {
            chk[v]=1;
            if(yM[v]==-1 || dfs(yM[v]))
            {
                yM[v]=u;
                xM[u]=v;
                return true;
            }
        }
    }
    return false;
}

int MaxMatch()
{
    int ans=0;
    for(int i=0;i<n;i++)
    {
        if(xM[i]==-1)
        {
            memset(chk,0,sizeof(chk));
            if(dfs(i))  ans++;
        }
    }
    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d",&n)==1)
    {
        memset(xM,-1,sizeof(xM));
        memset(yM,-1,sizeof(yM));
        memset(g,0,sizeof(g));
        for(int i=0;i<n;i++)
        {
            int t,x,y;
            scanf("%d: (%d)",&x,&t);
            for(int j=0;j<t;j++)
            {
                scanf("%d",&y);
                g[x][y]=g[y][x]=1;
            }
        }
        printf("%d\n",n-MaxMatch()/2);
    }

    return 0;
}
