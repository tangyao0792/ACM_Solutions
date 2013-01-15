#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>

using namespace std;

const double EPS=1e-12;
const int MAXN=210;
const int INF=1<<28;

double g[MAXN][MAXN],d[MAXN],x[MAXN],y[MAXN];
int v[MAXN];
int n, m;

double dis(int i, int j)
{
    return sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
}

double dij();
double min(double a, double b)
{
    if(a>b+EPS)
        return b;
    return a;
}
double max(double a, double b)
{
    if(a>b+EPS)
        return a;
    return b;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCount=0;
    while(scanf("%d",&n)==1&&n)
    {
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                g[i][j]=INF;
        nCount++;
        for(int i=0;i<n;i++)
            scanf("%lf %lf",&x[i],&y[i]);
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                g[i][j]=dis(i,j);
        printf("Scenario #%d\n",nCount);
        printf("Frog Distance = %.3f\n\n",dij());
    }
    return 0;
}

double dij()
{
    for(int i=0;i<n;i++)    d[i]=INF;
    d[0]=0;
    memset(v,0,sizeof(v));

    for(int i=0;i<n;i++)
    {
        int x;
        double m=INF;
        for(int y=0;y<n;y++)
        {
            if(!v[y]&&d[y]+EPS<m)
            {
                m=d[x=y];
            }
        }
        v[x]=1;
        for(int y=0;y<n;y++)
        {
            d[y]=min(d[y],max(d[x],g[x][y]));
        }
    }
    return d[1];
}
