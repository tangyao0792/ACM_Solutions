/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

const int INF=1<<30;
const int MAXN=303;
int n,m,s;
int mark[MAXN],g[MAXN][MAXN],w[MAXN];

int get_mincut(int &s,int &t)
{
    memset(mark,0,sizeof(mark));
    memset(w,0,sizeof(w));
    for(int i=2;i<=n;i++)
        w[i]=g[1][i];
    mark[1]=1;

    s=t=1;

    for(int i=1;i<n;i++)
    {
        int best=-1,x=0;
        for(int j=1;j<=n;j++)
        {
            if(!mark[j] && (best==-1 || best<w[j]))
            {
                best=w[j];
                x=j;
            }
        }

        if(i==n-2)
            s=x;
        if(i==n-1)
            t=x;
        mark[x]=1;
        for(int j=1;j<=n;j++)
            if(!mark[j])
                w[j]+=g[x][j];
    }
    return w[t];
}

inline void merge(int s,int t)
{
    for(int i=1;i<=n;i++)
    {
        g[s][i]+=g[t][i];
        g[i][s]+=g[i][t];
    }
    for(int i=1;i<n;i++)
    {
        g[i][t]=g[i][n];
        g[t][i]=g[n][i];
    }
    n--;
}

int solve()
{
    int mincut=INF,s,t;
    while(n>1)
    {
        int cut=get_mincut(s,t);
        if(mincut>cut)    mincut=cut;
        merge(s,t);
    }
    return mincut;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    while(scanf("%d %d %d",&n,&m,&s)==3)
    {
        if(n==0 && m==0 && s==0)
            break;

        memset(g,0,sizeof(g));
        for(int i=0;i<m;i++)
        {
            int x,y,z;
            scanf("%d %d %d",&x,&y,&z);
            g[x][y]+=z;
            g[y][x]+=z;
        }
        printf("%d\n",solve());
    }
    return 0;
}
