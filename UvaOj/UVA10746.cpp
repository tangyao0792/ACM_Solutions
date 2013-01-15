#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

const double EPS=1e-12;
const int MAXN=51;
const int INF=1<<28;

int cap[MAXN][MAXN], flow[MAXN][MAXN],fa[MAXN];
double w[MAXN][MAXN], d[MAXN];
bool inq[MAXN];

int n,m;

double minmax()
{
    double ans=0;
    for(;;)
    {
        for(int i=0;i<MAXN;i++) d[i]=INF;
        memset(inq,false,sizeof(inq));
        memset(fa,-1,sizeof(fa));
        d[0]=0;
        queue<int> q;
        q.push(0);
        while(!q.empty())
        {
            int x=q.front();
            q.pop();
            inq[x]=false;
            for(int v=0;v<=50;v++)
            {
                if(d[v]>d[x]+w[x][v]+EPS
                   &&cap[x][v]>flow[x][v])
                {
                    d[v]=d[x]+w[x][v];
                    fa[v]=x;
                    if(!inq[v])
                    {
                        inq[v]=true;
                        q.push(v);
                    }
                }
            }
        }
        if(!(d[50]+EPS<INF))    break;
        int a=INF;
        for(int v=50;v!=0;v=fa[v])
        {
            a=min(a,cap[fa[v]][v]-flow[fa[v]][v]);
        }
        for(int v=50;v!=0;v=fa[v])
        {
            flow[fa[v]][v]+=a;
            flow[v][fa[v]]-=a;
        }
        ans+=a*d[50];
    }
    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d %d",&n,&m)==2 && n&&m)
    {
        memset(cap,0,sizeof(cap));
        memset(flow,0,sizeof(flow));

        for(int i=0;i<MAXN;i++)
            for(int j=0;j<MAXN;j++)
                w[i][j]=INF;

        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
            {
                cap[0][j]=1;
                w[0][j]=0;
                w[j][0]=0;
                cap[j][i+25]=1;
                cap[i+25][50]=1;
                w[i+25][50]=0;
                w[50][i+25]=0;
                scanf("%lf",&w[j][i+25]);
                w[i+25][j]=-w[j][i+25];
            }
        printf("%.2lf\n",(1e-6+minmax())/n);//¾«¶ÈÆ«ÒÆ
    }
    return 0;
}
