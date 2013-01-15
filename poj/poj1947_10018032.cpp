#include<cstdio>
#include<cstring>
#include<iostream>
#include<vector>

using namespace std;

const int INF=1<<28;
const int MAXN=155;

int min(int a,int b){return a<b?a:b;}

vector<int> v[155];

int dp[MAXN][MAXN];
int d[MAXN];        //入度
int n,p;

void dfs(int root)
{
    int s=v[root].size();
    for(int i=0;i<s;i++)    dfs(v[root][i]);


    for(int i=0;i<s;i++)
    {
        int son=v[root][i];
        for(int j=p;j>=2;j--)
        {
            for(int k=1;k<j;k++)
            {
                dp[root][j]=min(dp[root][j],dp[son][k]+dp[root][j-k]-2);
            }
        }
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif

    scanf("%d %d",&n,&p);

    memset(d,0,sizeof(d));

    int x,y;
    for(int i=0;i<n-1;i++)
    {
        scanf("%d %d",&x,&y);
        v[x].push_back(y);
        d[y]++;
    }

    int root;
    for(int i=1;i<=n;i++)
        if(d[i]==0)
        {
            root=i;
            break;
        }


    for(int i=1;i<=n;i++)
    {
        int s=v[i].size();
        dp[i][1]=s+1;
        for(int j=2;j<=p;j++)
            dp[i][j]=INF;
    }

    dfs(root);
    dp[root][p]--;
    int ans=INF;
    for(int i=1;i<=n;i++)
        ans=min(ans,dp[i][p]);
    printf("%d\n",ans);
    return 0;
}
