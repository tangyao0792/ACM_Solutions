#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>

using namespace std;

const double EPS=1e-12;
const int INF = 1<<28;
double g[35][35];
int n, m;
map<string,int> mapm;

bool Flyod();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("last.txt", "r", stdin);
    //freopen("out.txt", "w",stdout);
#endif
    int nCount=0;
    while(scanf("%d",&n) >0 && n)
    {
        nCount++;
        for(int i=0;i<35;i++)
            for(int j=0;j<35;j++)   g[i][j]=0;

        mapm.clear();
        for(int i=0;i<n;i++)
        {
            g[i][i]=1;
            string line;
            cin>>line;
            mapm[line]=i;
        }
        scanf("%d",&m);
        for(int i=0;i<m;i++)
        {
            string a, b;
            int x,y;
            double w;
            cin>>a>>w>>b;
            x=mapm[a];
            y=mapm[b];
            g[x][y]=w;
        }
        if(Flyod()) printf("Case %d: Yes\n",nCount);
        else    printf("Case %d: No\n",nCount);
    }
    return 0;
}

bool Flyod()
{
    for(int k=0;k<n;k++)
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
            {

                if(g[i][j]<g[i][k]*g[k][j])
                    g[i][j]=g[i][k]*g[k][j];
                if(i==j&&g[i][j]>1) return true;
            }
    for(int k=0;k<n;k++)
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if(g[i][k]*g[k][j]-g[i][j]>EPS)
                    return true;

//    for(int i=0;i<n;i++)
//        if(g[i][i]>1)   return true;

    return false;

}
