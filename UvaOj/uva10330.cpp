#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>

using namespace std;

const int MAXN=210;
const int INF=1<<28;

int cap[MAXN][MAXN],flow[MAXN][MAXN],a[MAXN],fa[MAXN];

int n,m;
int EK();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d",&n)==1)
    {
        memset(cap,0,sizeof(cap));
        memset(flow,0,sizeof(flow));
        for(int i=1;i<=n;i++)
        {
            int c;
            scanf("%d",&c);
            cap[i*2-1][i*2]=c;
        }
        scanf("%d",&m);
        for(int i=0;i<m;i++)
        {
            int x,y,z;
            scanf("%d %d %d",&x,&y,&z);
            cap[2*x][2*y-1]=z;
        }
        int b,d;
        scanf("%d %d",&b,&d);
        for(int i=0;i<b;i++)
        {
            int t;
            scanf("%d",&t);
            cap[0][2*t-1]=INF;
        }
        for(int i=0;i<d;i++)
        {
            int t;
            scanf("%d",&t);
            cap[2*t][2*(n+1)-1]=INF;
        }
        printf("%d\n",EK());
    }
    return 0;
}

int EK()
{
    queue<int> q;
    int f=0;
    int t=2*n+1;
    for(;;)
    {
        memset(a,0,sizeof(a));
        a[0]=INF;
        q.push(0);
        while(!q.empty())
        {
            int u=q.front();
            q.pop();

            for(int v=0;v<=t;v++)
            {
                if(!a[v] && cap[u][v]>flow[u][v])
                {
                    a[v]=min(a[u],cap[u][v]-flow[u][v]);
                    q.push(v);
                    fa[v]=u;
                }
            }
        }
        if(a[t]==0) break;
        for(int u=t;u!=0;u=fa[u])
        {
            flow[fa[u]][u]+=a[t];
            flow[u][fa[u]]-=a[t];
        }
        f+=a[t];
    }
    return f;
}
