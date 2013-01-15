#include<cstdio>
#include<iostream>
#include<cstring>

using namespace std;

const int MAXN=110;
const int INF=100000;
int g[MAXN][MAXN];
int n;

void floyd();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif

    while(scanf("%d",&n)==1 && n)
    {
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                g[i][j]=INF;

        for(int i=1;i<=n;i++)
        {
            int m;
            scanf("%d",&m);
            for(int j=0;j<m;j++)
            {
                int p,t;
                scanf("%d %d",&p,&t);
                g[i][p]=t;
            }
            g[i][i]=0;
        }
        floyd();
        int index,nMin=INF;
        for(int i=1;i<=n;i++)
        {
            int nMax=0,sum=0;
            for(int j=1;j<=n;j++)if(i!=j)
            {
                if(g[i][j]<INF)
                    sum++;
                if(g[i][j]>nMax)
                    nMax=g[i][j];
            }
            if(nMax<nMin && sum==n-1)
            {
                nMin=nMax;
                index=i;
            }
        }
        if(nMin==INF)
            printf("disjoint\n");
        else
            printf("%d %d\n",index,nMin);
    }

    return 0;
}

void floyd()
{
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                if(g[i][j]>g[i][k]+g[k][j])
                {
                    g[i][j]=g[i][k]+g[k][j];
                }
}
