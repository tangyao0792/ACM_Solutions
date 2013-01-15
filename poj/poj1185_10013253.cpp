#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;

const int MAXN=110;
const int MAXS=65;

int n,m;
int map[MAXN];
int cnt;
int st[MAXS];       //状态
int num[MAXS];      //num[i]表示st[i]时炮台的数量
int dp[3][MAXS][MAXS];
//dp[r][i][j]   表示第r行状态为st[i]时，第r-1行状态为j时
//前r行的数量
//dp[r][i][j]=max(dp[r][i][j],dp[r-1][j][k]+num[i])

bool isOk(int x)
{
    if(x&(x<<1))    return false;
    if(x&(x<<2))    return false;
    return true;
}

void countState()
{
    int cnt=0;
    for(int i=0;i<(1<<10)+1;i++)
        if(isOk(i))
            cnt++;
    printf("%d",cnt);
}

int getNum(int x)
{
    int ans=0;

    for(int i=1;i<=x;i=i<<1)
        if(i & x)
            ans++;

    return ans;
}

void makeState()
{
    cnt=0;
    for(int i=0;i<(1<<m);i++)
        if(isOk(i))
        {
            st[cnt]=i;
            num[cnt++]=getNum(i);
        }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif

    memset(map,0,sizeof(map));
    memset(dp,-1,sizeof(dp));

    cin>>n>>m;
    char c;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        {
            cin>>c;
            if(c=='H')
                map[i]=map[i]|(1<<j);
        }

    makeState();

    for(int i=0;i<cnt;i++)          //第0行
    {
        if(st[i] & map[0])  continue;
        dp[0][i][0]=num[i];
    }

    for(int i=0;i<cnt;i++)          //第1行
    {
        if(st[i] & map[0])  continue;
        for(int j=0;j<cnt;j++)
        {
            if(st[j] & st[i])   continue;
            if(st[j] & map[1])  continue;

            dp[1][j][i]=max(dp[1][j][i],dp[0][i][0]+num[j]);
        }
    }

    for(int r=2;r<n;r++)
    {
        for(int i=0;i<cnt;i++)      //第r行的状态
        {
            if(st[i] & map[r])  continue;
            for(int j=0;j<cnt;j++)  //r-1
            {
                if(st[i] & st[j])   continue;
                for(int k=0;k<cnt;k++)  //r-2
                {
                    if(st[i] & st[k])   continue;
                    if(dp[(r-1)%3][j][k]==-1)   continue;

                    dp[(r)%3][i][j]=max(dp[r%3][i][j],dp[(r-1)%3][j][k]+num[i]);
                }
            }
        }
    }
    int ans=-1;
    for(int i=0;i<cnt;i++)
        for(int j=0;j<cnt;j++)
            ans=max(ans,dp[(n-1)%3][i][j]);

    printf("%d\n",ans);
    return 0;
}
