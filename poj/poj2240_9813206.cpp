#include<cstdio>
#include<iostream>
#include<cstring>
#include<map>

using namespace std;

const int MAXN=35;
const int INF=1<<28;
const double EPS=1e-12;

double g[MAXN][MAXN];
int n;

bool floyd();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCount=0;
    while(scanf("%d",&n)==1 && n)
    {
        nCount++;
        map<string,int> m;
        memset(g,0,sizeof(g));
        string tmp;
        for(int i=0;i<n;i++)
        {
            cin>>tmp;
            m[tmp]=i;
        }
        int k;
        scanf("%d",&k);
        for(int i=0;i<k;i++)
        {
            string a,b;
            double tmp;
            cin>>a>>tmp>>b;
            g[m[a]][m[b]]=tmp;
        }
        if(floyd())
        {
            printf("Case %d: Yes\n",nCount);
        }
        else
        {
            printf("Case %d: No\n",nCount);
        }
    }
    return 0;
}

bool floyd()
{
    for(int k=0;k<n;k++)
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
                if(g[i][j]+EPS<g[i][k]*g[k][j])
                    g[i][j]=g[i][k]*g[k][j];
            if(g[i][i]>1.0+EPS)
                return true;
        }
    for(int i=0;i<n;i++)
        if(g[i][i]>1.0+EPS)
            return true;
    return false;
}
