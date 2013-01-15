#include<cstdio>
#include<cstring>
#include<cmath>

const int MAXN = 760;
const int INF = 1<<28;
int n,m;
int x[MAXN],y[MAXN],v[MAXN];
double d[MAXN][MAXN], lowc[MAXN];

double dis(int i, int j)
{
    return sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
}

double prim();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    while(scanf("%d",&n)>0)
    {
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                d[i][j]=INF;

        for(int i=1;i<=n;i++)
        {
            scanf("%d %d",&x[i], &y[i]);
        }
        for(int i=1;i<=n;i++)
        {
            for(int j=i+1;j<=n;j++)
            {
                d[i][j]=d[j][i]=dis(i,j);
            }
        }
        scanf("%d",&m);
        for(int i=0;i<m;i++)
        {
            int u,v;
            scanf("%d %d",&u,&v);
            d[u][v]=d[v][u]=0;
        }
        printf("%.2lf\n",prim());
    }
    return 0;
}

double prim()
{
    memset(v,0,sizeof(v));
    double ans=0;
    for(int i=1;i<=n;i++)
        lowc[i]=d[1][i];
    v[1]=1;
    double mindis;
    int minone;
    for(int k=0;k<n-1;k++)
    {
        mindis=INF;
        for(int i=1;i<=n;i++)
        {
            if(!v[i] && mindis>lowc[i])
            {
                mindis=lowc[i];
                minone=i;
            }
        }
        ans+=lowc[minone];
        v[minone]=1;
        for(int i=1;i<=n;i++)
        {
            if(!v[i] && d[i][minone]<lowc[i])
            {
                lowc[i]=d[i][minone];
            }
        }
    }
    return ans;
}
