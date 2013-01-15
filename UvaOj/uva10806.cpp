#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

const int INF=1<<28;
const int MAXN=110;

int g[MAXN][MAXN],d[MAXN],inq[MAXN],fa[MAXN];
int n,m,cnt;

int spfa();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    while(scanf("%d",&n)==1 && n)
    {
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                g[i][j]=INF;
        scanf("%d",&m);
        for(int i=0;i<m;i++)
        {
            int x,y,z;
            scanf("%d %d %d",&x,&y,&z);
            g[x][y]=g[y][x]=z;
        }
        int ans1=spfa();
        int ans2=spfa();
        if(ans1&&ans2)
            printf("%d\n",ans1+ans2);
        else
            printf("Back to jail\n");
    }
    return 0;
}

int spfa()
{
    memset(inq,0,sizeof(inq));
    memset(fa,-1,sizeof(fa));
    for(int i=2;i<=n;i++)   d[i]=INF;
    d[1]=0;
    queue<int> q;
    q.push(1);
    while(!q.empty())
    {
        int x=q.front();
        q.pop();
        inq[x]=0;
        for(int u=1;u<=n;u++)
        {
            if(d[u]>d[x]+g[x][u])
            {
                d[u]=d[x]+g[x][u];
                fa[u]=x;
                if(!inq[u])
                {
                    inq[u]=1;
                    q.push(u);
                }
            }
        }
    }
    if(d[n]==INF)   return 0;
    for(int t=n;t!=1;t=fa[t])
    {
        g[fa[t]][t]=INF;
        g[t][fa[t]]=-g[t][fa[t]];
    }
    return d[n];
}
