/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
#define maxn 262144
#define ll int
__int64 dp[maxn][18];
ll g[18][18];
ll mark[maxn];
ll state[18][48620];
ll len[18];
void make_state()
{
    int i,j,n=18;
    for(i=1;i<maxn;i++)
    {
        for(j=0;j<n;j++)
        {
            if(i&(1<<j))mark[i]++;
        }
    }
    for(i=1;i<maxn;i++)
    {
        int t=mark[i];
        state[t-1][len[t-1]]=i;
        len[t-1]++;
    }
    len[0]=1;
}
int main()
{
    make_state();
    ll n,m,i,j,k,x,y,s,f,p;
// freopen("in.txt","r",stdin);
// freopen("out2.txt","w",stdout);
 while(scanf("%d%d",&n,&m)!=EOF)
    //while(scanf("d%I64%I64d",&n,&m)!=EOF)
    {
        memset(g,0,sizeof(g));
        s=1<<n;
        for(i=0;i<m;i++)
        {
            //scanf("%I64d%I64d",&x,&y);
   scanf("%d%d",&x,&y);
            x--;y--;
            g[x][y]=g[y][x]=1;
        }
  for(i=0;i<s;i++)
  {
   for(j=0;j<n;j++)
   {
    dp[i][j]=0;
   }
  }
        dp[1][0]=1;
        for(i=0;i<n-1;i++)//第i层
        {
            for(j=0;j<len[i];j++)//i-1层的第j个元素出发
            {
                k=state[i][j];//k是状态
                if(k>s)break;
                for(f=0;f<n;f++)//f在状态k中
                {
                    if(k&(1<<f)&&dp[k][f])
                    for(p=0;p<n;p++)//p不再状态k中，和f相邻
                    {
                        if(g[p][f]&&(!(k&(1<<p))))
                        {
                            dp[k+(1<<p)][p]+=dp[k][f];
                        }
                    }
                }
            }
        }
        __int64 ans=0;
        for(i=0;i<n;i++)
        {
            if(g[i][0])ans+=dp[s-1][i];
        }
  printf("%I64d\n",ans);
       // printf("%I64d\n",ans);
    }
    return 0;
}
