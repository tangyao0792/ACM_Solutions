#include<cstdio>
#include<iostream>
#include<cstring>

using namespace std;

const double EPS=1e-12;
double g[30][30][30];
int path[30][30][30];
int n;

void Floyd();
void printpath(int x,int y,int s);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d",&n)>0)
    {
        memset(g,0,sizeof(g));
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if(i!=j)    scanf("%lf",&g[i][j][0]);
                else   g[i][j][0]=1;
        Floyd();

    }
    return 0;
}

void printpath(int i,int j,int s)
{
    if(s==-1)
    {
        printf("%d",j+1);
    }
    else
    {
        printf("%d ",i+1);
        printpath(path[i][j][s],j,s-1);
    }
}

void Floyd()
{
    memset(path,0,sizeof(path));
    for(int step=1;step<n;step++)
    {
        for(int k=0;k<n;k++)
            for(int i=0;i<n;i++)
                for(int j=0;j<n;j++)
                    if(g[i][j][step]+EPS < g[i][k][0]*g[k][j][step-1])
                    {
                        g[i][j][step]=g[i][k][0]*g[k][j][step-1];
                        path[i][j][step]=k;
                    }

        for(int i=0;i<n;i++)
        {
            if(g[i][i][step]>1.01+EPS)
            {
                printpath(i,i,step);
                printf("\n");
                return;
            }
        }
    }
    printf("no arbitrage sequence exists\n");
}
