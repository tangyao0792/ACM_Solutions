#include<cstdio>
#include<cstring>
#include<vector>
#include<iostream>

using namespace std;

const int MAXN=3010;
const int INF=1<<28;

vector<int> v[MAXN];
int income[MAXN];
int dp[MAXN][MAXN];
int n,m;

int dfs(int root)
{
    int s=v[root].size();

    for(int i=0;i<=m;i++)
        dp[root][i]=-INF;
    dp[root][0]=0;

    int sum=0;

    for(int i=0;i<s;i++)
    {
        int son=v[root][i];
        sum+=dfs(v[root][i]);
        for(int k=sum;k>0;k--)
        {
            for(int j=0;j<k;j++)
            {
                dp[root][k]=
                    max(dp[root][k],
                        dp[root][j]+dp[son][k-j]);
            }
        }
    }
    for(int i=1;i<=m;i++)
        dp[root][i]+=income[root];
    if(s==0)
    {
         dp[root][1]=income[root];
         return 1;
    }

    return sum;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif

    scanf("%d %d",&n,&m);

    for(int i=1;i<=n-m;i++)
    {
        int k,a,c;
        scanf("%d",&k);
        for(int j=0;j<k;j++)
        {
            scanf("%d %d",&a,&c);
            v[i].push_back(a);
            income[a]=-c;
        }
    }

    for(int i=n-m+1;i<=n;i++)
    {
        int tmp;
        scanf("%d",&tmp);
        income[i]+=tmp;
    }

    dfs(1);

    for(int i=m;i>=0;i--)
        if(dp[1][i]>=0)
        {
            printf("%d\n",i);
            break;
        }

    return 0;
}
