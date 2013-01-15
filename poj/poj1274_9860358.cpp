#include<cstdio>
#include<cstring>

const int MAXN=210;

int uN, vN;
bool g[MAXN][MAXN];
int xM[MAXN],yM[MAXN];
bool chk[MAXN];

bool SearchPath(int u)
{
    for(int v=1;v<=vN;v++)
    {
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
    }
    return false;
}

int MaxMatch()
{
    int ans=0;
    memset(xM,-1,sizeof(xM));
    memset(yM,-1,sizeof(yM));
    for(int u=1;u<=uN;u++)
    {
        if(xM[u]==-1)
        {
            memset(chk,0,sizeof(chk));
            if(SearchPath(u))   ans++;
        }
    }
    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d %d",&uN, &vN)==2)
    {
        memset(g,0,sizeof(g));

        for(int i=1;i<=uN;i++)
        {
            int s;
            scanf("%d",&s);
            for(int j=0;j<s;j++)
            {
                int x;
                scanf("%d",&x);
                g[i][x]=true;
            }
        }
        printf("%d\n",MaxMatch());
    }
    return 0;
}
