#include<cstdio>
#include<cstring>

const int MAXN=1010;
const int MAXM=110;
const int MAXS=60000;
const int t[5]={1,10,100,1000,10000};
const int INF=1<<28;

int min(int a,int b){return a<b?a:b;}

int price[MAXN];
int bag[5];
int at[MAXN];       //code为c的物品在第几个bag里

int dp[MAXS];        //dp[i]表示状态为i的价格
int st[MAXM][2];        //st[i][0]表示状态st[i][1]表示价格

int b,s,cnt;

int calcSt(int x,int y)
{
    int ans=0;
    for(int i=4;i>=0;i--)
    {
        int a=x/t[i];
        int b=y/t[i];
        x%=t[i];
        y%=t[i];

        if(b>a) return -1;
        ans+=(a-b)*t[i];
    }
    return ans;
}

int dfs(int x)
{
    if(dp[x]!=-1)   return dp[x];
    if(x==0)    return 0;

    int ans=INF;
    for(int i=0;i<cnt;i++)
    {
        int tmp=calcSt(x,st[i][0]);
        if(tmp!=-1)
        {
            ans=min(ans,dfs(tmp)+st[i][1]);
        }
    }
    return dp[x]=ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif

    while(scanf("%d",&b)==1)
    {
        memset(at,-1,sizeof(at));
        memset(dp,-1,sizeof(dp));
        cnt=0;
        int start=0;
        for(int i=0;i<b;i++)        //计算初始状态
        {
            int c,k,p;
            scanf("%d %d %d",&c,&k,&p);
            bag[i]=c;               //
            at[c]=i;
            price[c]=p;
            start+=k*t[i];
            st[cnt][0]=t[i];
            st[cnt++][1]=p;
        }

        scanf("%d",&s);
        for(int i=0;i<s;i++)
        {
            int n;
            scanf("%d",&n);
            int c,k,p,tmp=0;
            bool in=true;
            for(int j=0;j<n;j++)
            {
                scanf("%d %d",&c,&k);
                if(at[c]==-1)
                {
                    in=false;
                    break;
                }
                tmp+=k*t[at[c]];
            }
            scanf("%d",&p);
            if(in)
            {
                st[cnt][0]=tmp;
                st[cnt++][1]=p;
            }
        }

        printf("%d\n",dfs(start));
    }

    return 0;
}
