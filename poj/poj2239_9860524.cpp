#include<cstdio>
#include<cstring>

const int MAXN=100;
const int MAXM=310;
bool g[MAXM][MAXN];
int uN,vN;
int xM[MAXM],yM[MAXN];
bool chk[MAXM];

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
    memset(xM,-1,sizeof(xM));
    memset(yM,-1,sizeof(yM));
    int ans=0;
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
    while(scanf("%d",&uN)==1)
    {
        memset(g,0,sizeof(g));
        vN=99;
        int t;
        for(int i=1;i<=uN;i++)
        {
            scanf("%d",&t);
            for(int j=0;j<t;j++)
            {
                int p,q;
                scanf("%d %d",&p,&q);
                g[i][(p-1)*13+q]=true;
            }
        }
        printf("%d\n",MaxMatch());
    }
    return 0;
}
