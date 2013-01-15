#include<cstdio>
#include<cstring>

#define max(a,b) (a>b?a:b)

const int MAXN=110;

bool g[MAXN][MAXN];
int x[MAXN],y[MAXN],z[MAXN],d[MAXN],v[MAXN];
int n;

void init()
{
    for(int i=0;i<n;i++)
    {
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        x[i*3]=a;y[i*3]=b;z[i*3]=c;
        x[i*3+1]=b;y[i*3+1]=c;z[i*3+1]=a;
        x[i*3+2]=a;y[i*3+2]=c;z[i*3+2]=b;
    }
    memset(g,0,sizeof(g));
    for(int i=0;i<3*n;i++)
        for(int j=0;j<3*n;j++)
            if((x[i]<x[j]&&y[i]<y[j])
               || (x[i]<y[j] && y[i]<x[j]) )
            g[i][j]=true;

    memset(v,0,sizeof(v));
}

int dp(int x)
{
    if(v[x])    return d[x];
    v[x]=1;
    int nMax=0;
    for(int i=0;i<3*n;i++)
    {
        if(g[x][i])
            nMax=max(nMax,dp(i));
    }
    return d[x]=nMax+z[x];
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase=0;
    while(scanf("%d", &n)==1 && n)
    {
        nCase++;
        init();
        int nMax=0;
        for(int i=0;i<3*n;i++)
        {
            nMax=max(nMax,dp(i));
        }
        printf("Case %d: maximum height = %d\n",nCase,nMax);
    }
    return 0;
}
