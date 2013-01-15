#include<cstdio>
#include<cstring>

const int MAXN=110;
const int N=16;
const int INF=1<<28;

int g[MAXN][MAXN*2];       //g[i][i]表示上边的颜色
int rec[N][5];
int dp[1<<17];
int cond[1<<17];        //只有(st&cond[i]==cond[i])时，才算满足条件
int n,end;
int vis[N];

int min(int a,int b){return a<b?a:b;}

void makeCondition()
{
    for(int i=1;i<=n;i++)
    {
        cond[i]=0;
        int y=rec[i][0];
        int x1=rec[i][1];
        int x2=rec[i][3];

        for(int j=2*x1;j<2*x2;j++)
            if(g[y][j])
                cond[i]=cond[i]|(1<<g[y][j]);
    }
}

int dfs(int x,int r)
{
   // if(dp[x]!=-1)   return dp[x];
    if(x==end)
        return 0;
    int ans=INF;
    for(int i=1;i<=n;i++)
    {
        if((x&cond[i])==cond[i] && !vis[i])
        {
            vis[i]=1;
            ans=min(ans,dfs(x|(1<<i),rec[i][4])+(rec[i][4]==r?0:1));
            vis[i]=0;
        }
    }
    return dp[x]=ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    int M;
    scanf("%d",&M);
    while(M--)
    {
        memset(dp,-1,sizeof(dp));
        memset(g,0,sizeof(g));
        memset(vis,0,sizeof(vis));
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            int x1,y1,x2,y2,r;
            scanf("%d %d %d %d %d",&y1,&x1,&y2,&x2,&r);
            for(int j=2*x1;j<2*x2;j++)
            {
                g[y2][j]=i;
            }
            rec[i][0]=y1;rec[i][1]=x1;rec[i][2]=y2;rec[i][3]=x2;
            rec[i][4]=r;
        }
        end=(1<<n)-1;
        end=end<<1;
        makeCondition();
        printf("%d\n",dfs(0,0));
    }
    return 0;
}
