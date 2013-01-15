#include<cstdio>
#include<cstring>

const int MAXN=1510;
const int MAXM=MAXN*2;

int first[MAXN],vis[MAXN];
int u[MAXM],v[MAXM],next[MAXM];

int ft[MAXN];
int ut[MAXM],vt[MAXM],nt[MAXM];

int d[MAXN][2];

int n,cnt;

int max(int a,int b){return a>b?a:b;}
int min(int a,int b){return a<b?a:b;}

void addedge(int x,int y)
{
    u[cnt]=x,v[cnt]=y;
    next[cnt]=first[x];
    first[x]=cnt++;
}
void AddTreeEdge(int x,int y)
{
    ut[cnt]=x,vt[cnt]=y;
    nt[cnt]=ft[x];
    ft[x]=cnt++;
}

void dfs(int x)
{
    for(int e=first[x];e!=-1;e=next[e])
    {
        int y=v[e];
        if(vis[y])  continue;
        vis[y]=1;

        AddTreeEdge(x,y);
        dfs(y);
    }
}

void dp(int x)
{
    if(vis[x])  return;

    d[x][1]=d[x][0]=0;
    for(int e=ft[x];e!=-1;e=nt[e])
    {
        int y=vt[e];
        dp(y);
        d[x][1]+=min(d[y][0],d[y][1]);
        d[x][0]+=d[y][1];
    }
    d[x][1]++;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif

    while(scanf("%d",&n)==1 && n)
    {
        cnt=0;
        memset(vis,0,sizeof(vis));
        memset(first,-1,sizeof(first));
        memset(ft,-1,sizeof(ft));
        int x,k,y;
        for(int i=0;i<n;i++)
        {
            scanf("%d:(%d)",&x,&k);
            while(k--)
            {
                scanf("%d",&y);
                addedge(x,y);
                addedge(y,x);
            }
        }
        cnt=0;
        vis[0]=1;
        dfs(0);

        memset(vis,0,sizeof(vis));
        dp(0);

        printf("%d\n",min(d[0][1],d[0][0]));
    }
    return 0;
}
