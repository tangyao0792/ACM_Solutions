#include<cstdio>
#include<cstring>

const int MAXN=2010;
const int INF=1<<28;

int n;
int g[MAXN][MAXN],low[MAXN],vis[MAXN];
char str[MAXN][10];

int dis(int i,int j)
{
    int ans=0;
    for(int k=0;k<7;k++)
        if(str[i][k]!=str[j][k])
            ans++;

    return ans;
}

int prim()
{
    int ans=0;
    memset(vis,0,sizeof(vis));
    for(int i=0;i<n;i++)    low[i]=g[0][i];
    vis[0]=1;

    int mindis,minone;

    for(int k=0;k<n-1;k++)
    {
        mindis=INF;
        for(int i=0;i<n;i++)
        {
            if(!vis[i] && mindis>low[i])
            {
                mindis=low[i];
                minone=i;
            }
        }
        ans+=mindis;
        vis[minone]=1;
        for(int i=0;i<n;i++)
        {
            if(low[i]>g[minone][i])
            {
                low[i]=g[minone][i];
            }
        }
    }
    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif

    while(scanf("%d",&n)==1 && n)
    {
        for(int i=0;i<n;i++)
            scanf("%s",str[i]);

        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                g[i][j]=dis(i,j);

        printf("The highest possible quality is 1/%d.\n",prim());
    }

    return 0;
}
