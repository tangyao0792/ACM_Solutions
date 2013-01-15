#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

const int MAXN = 110;
const int MAXM = 110*110/2;
int n, m;
double w[MAXM];
double x[MAXN],y[MAXN];
int u[MAXM],v[MAXM],r[MAXM],p[MAXN];

int find(int x){return p[x]==-1?x:(p[x]=find(p[x]));}
double dis(int i, int j)
{
    return sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
}
bool comp(int a, int b){return w[a]<w[b];}
double Kruskal();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r", stdin);
#endif
    int nCase;
    scanf("%d",&nCase);
    while(nCase--)
    {
        scanf("%d",&n);
        for(int i=0;i<n;i++)
        {
            scanf("%lf %lf",&x[i],&y[i]);
        }
        m=0;
        for(int i=0;i<n;i++)
            for(int j=i+1;j<n;j++)
            {
                u[m]=i;
                v[m]=j;
                w[m++]=dis(i,j);
            }
        printf("%.2lf\n",Kruskal());
        if(nCase)printf("\n");
    }
}

double Kruskal()
{
    double ans = 0;
    memset(p,-1,sizeof(p));
    for(int i=0;i<m;i++)    r[i]=i;
    sort(r,r+m,comp);
    for(int i=0;i<m;i++)
    {
        int e=r[i];
        int x=find(u[e]);
        int y=find(v[e]);
        if(x!=y)
        {
            ans+=w[e];
            p[x]=y;
        }
    }
    return ans;
}
