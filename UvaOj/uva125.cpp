#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

int n,m;

int g[110][110];

void floyd();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    int nCount=0;
    while(scanf("%d",&m)==1)
    {
        memset(g,0,sizeof(g));
        n=0;
        for(int i=0;i<m;i++)
        {
            int x,y;
            scanf("%d %d",&x,&y);
            if(n<x) n=x;
            if(n<y) n=y;
            g[x][y]=1;
        }
        n++;
        floyd();
        printf("matrix for city %d\n",nCount);
        nCount++;
        for(int i=0;i<n;i++)
        {
            printf("%d",g[i][0]);

            for(int j=1;j<n;j++)
                printf(" %d",g[i][j]);
            printf("\n");
        }

    }
    return 0;
}

void floyd()
{
    for(int k=0;k<n;k++)
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
            {
                g[i][j]+=g[i][k]*g[k][j];
            }

    for(int k=0;k<n;k++)
    {
        if(g[k][k])
        {
            for(int i=0;i<n;i++)
                for(int j=0;j<n;j++)
                    if(g[i][k] && g[k][j])
                        g[i][j]=-1;
        }
    }
}
