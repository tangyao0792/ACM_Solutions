#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

const int INF=1<<28;
const int MAXN=110;
int g[MAXN][MAXN],l[MAXN],d[MAXN],v[MAXN];
int n, m;

int dij();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    scanf("%d %d",&m,&n);

    for(int i=0;i<=n;i++)
        for(int j=0;j<=n;j++)
            g[i][j]=INF;
    for(int i=1;i<=n;i++)
    {
        int t;
        scanf("%d %d %d",&g[0][i],&l[i],&t);
        for(int j=0;j<t;j++)
        {
            int e,w;
            scanf("%d %d",&e,&w);
            g[e][i]=w;
        }
    }
    int mindis=INF;
    for(int i=1;i<=n;i++)
    {
        int minlevel = l[i];
        memset(v,0,sizeof(v));
        for(int j=1;j<=n;j++)
        {
            if(l[j]<minlevel||l[j]>minlevel+m)
                v[j]=1;
        }
        int tmp=dij();
        if(tmp<mindis)  mindis=tmp;
    }
    printf("%d\n",mindis);

    return 0;
}

int dij()
{
    for(int i=0;i<=n;i++)     d[i]=INF;
    d[0]=0;
    for(int i=0;i<=n;i++)
    {
        bool flag=false;
        int x,min=INF;
        for(int y=0;y<=n;y++)
        {
            if(!v[y] && d[y]<min)
            {
                flag=true;
                min=d[x=y];
            }
        }
        if(!flag)break;
        v[x]=1;
        for(int y=0;y<=n;y++)
        {
            if(!v[y] && d[y]>d[x]+g[x][y])
            {
                d[y]=d[x]+g[x][y];
            }
        }
    }
    return d[1];
}
