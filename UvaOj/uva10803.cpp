#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>

using namespace std;

const int MAXN=110;
const double INF=1<<28;
const double EPS=1e-5;

double g[MAXN][MAXN],x[MAXN],y[MAXN];
int n;

double dis(int i,int j)
{
    return sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
}

void floyd();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase, iCase;
    scanf("%d",&nCase);
    for(iCase=1;iCase<=nCase;iCase++)
    {
        scanf("%d",&n);
        for(int i=0;i<n;i++)
        {
            scanf("%lf %lf",&x[i],&y[i]);
        }
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
            {
                g[i][j]=dis(i,j);
                if(g[i][j]>10.0+EPS)
                    g[i][j]=INF;
            }
        floyd();
        double max=0;
        bool flag=true;
        for(int i=0;i<n&&flag;i++)
            for(int j=0;j<n&&flag;j++)
            {
                if(g[i][j]>max+EPS)
                    max=g[i][j];
                if(g[i][j]>INF-1)
                    flag=false;
            }

        printf("Case #%d:\n",iCase);
        if(flag)
            printf("%.4lf\n",max);
        else
            printf("Send Kurdy\n");
        printf("\n");
    }
    return 0;
}

void floyd()
{
    for(int k=0;k<n;k++)
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if(g[i][j]>g[i][k]+g[k][j]+EPS)
                    g[i][j]=g[i][k]+g[k][j];
}
