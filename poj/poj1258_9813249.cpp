#include<cstdio>
#include<iostream>
#include<cstring>

using namespace std;

const int MAXN=110;
const int INF=1<<28;

int g[MAXN][MAXN],lowc[MAXN],v[MAXN];
int n;

int prim();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d",&n)==1&&n)
    {
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                scanf("%d",&g[i][j]);
        printf("%d\n",prim());
    }
    return 0;
}

int prim()
{
    int ans=0;
    for(int i=0;i<n;i++)    lowc[i]=g[0][i];
    memset(v,0,sizeof(v));
    v[0]=1;
    for(int i=0;i<n-1;i++)
    {
        int minone,mindis=INF;
        for(int j=0;j<n;j++)
        {
            if(!v[j]&&mindis>lowc[j])
            {
                minone=j;
                mindis=lowc[j];
            }
        }
        ans+=mindis;
        v[minone]=1;
        for(int j=0;j<n;j++)
        {
            if(lowc[j]>g[minone][j])
                lowc[j]=g[minone][j];
        }
    }
    return ans;
}
