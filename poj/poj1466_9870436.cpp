#include<cstdio>
#include<cstring>

const int MAXN= 510;

int g[MAXN][MAXN],xM[MAXN],yM[MAXN];
bool chk[MAXN];
int uN,vN,n;

bool SearchPath(int u)
{
    for(int v=0;v<n;v++)
    {
        if(g[u][v] && !chk[v])
        {
            chk[v]=true;
            if(yM[v]==-1 || SearchPath(yM[v]))
            {
                yM[v]=u;xM[u]=v;
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

    for(int u=0;u<n;u++)
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
    while(scanf("%d",&n)==1)
    {
        memset(g,0,sizeof(g));
        for(int i=0;i<n;i++)
        {
            int x,y,z;
            scanf("%d: (%d)",&x,&y);
            for(int j=0;j<y;j++)
            {
                scanf("%d",&z);
                g[x][z]=g[z][x]=1;
            }
        }
        printf("%d\n",n-MaxMatch()/2);
    }
    return 0;
}
