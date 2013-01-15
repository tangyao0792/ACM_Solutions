/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

#define min(a,b) (a<b?a:b)

const int MAXN=110;

int s[110];
int dp[MAXN][2];
char tmp[MAXN];

bool isUpper(char c)
{
    if(c>='A' && c<='Z')
        return true;
    return false;
}

int solve(int n)
{
    dp[0][0]=0;
    dp[0][1]=1;

    for(int i=1;i<=n;i++)
        if(s[i])
        {
            dp[i][0]=min(dp[i-1][0]+1,dp[i-1][1]+1);
            dp[i][1]=min(dp[i-1][0]+1,dp[i-1][1]);
        }
        else
        {
            dp[i][0]=min(dp[i-1][0],dp[i-1][1]+1);
            dp[i][1]=min(dp[i-1][0]+1,dp[i-1][1]+1);
        }

    return min(dp[n][0],dp[n][1]+1)+n;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif

    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",tmp);
        int nLen=strlen(tmp);
        for(int i=0;i<nLen;i++)
            if(isUpper(tmp[i]))
                s[i+1]=1;
            else
                s[i+1]=0;

        printf("%d\n",solve(nLen));
    }

    return 0;
}
