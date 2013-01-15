#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>

using namespace std;

const int MAXN = 510;
const int MAXM = 510*510/2;
int x[MAXN],y[MAXN],p[MAXN];
int u[MAXM],v[MAXM],r[MAXM];

double w[MAXM],ans[MAXM];
int s, n, m;

bool comp(int a,int b){return w[a]<w[b];}
double dis(int i,int j)
{
    return sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
}
int find(int x){return p[x]==-1?x:(p[x]=find(p[x]));}
double Kruskal();
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase;
    scanf("%d",&nCase);
    while(nCase--)
    {
        scanf("%d %d",&s,&n);
        for(int i=0;i<n;i++)
        {
            scanf("%d %d",&x[i],&y[i]);
        }
        m=0;
        for(int i=0;i<n;i++)
        {
            for(int j=i+1;j<n;j++)
            {
                u[m]=i;
                v[m]=j;
                w[m++]=dis(i,j);
            }
        }
        printf("%.2lf\n",Kruskal());
    }

    return 0;
}

double Kruskal()
{
    memset(p,-1,sizeof(p));
    for(int i=0;i<m;i++)    r[i]=i;
    sort(r,r+m,comp);
    int cnt=0;
    for(int i=0;i<m;i++)
    {
        int e=r[i];
        int x=find(u[e]);
        int y=find(v[e]);
        if(x!=y)
        {
            ans[cnt++]=w[e];
            p[x]=y;
        }
    }
    sort(ans,ans+cnt);
    return ans[cnt-s];
}
