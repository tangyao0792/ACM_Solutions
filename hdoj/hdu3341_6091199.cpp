/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
using namespace std;
int n,cnt;
int dp[500][20000];
int num[4];
int bin[4];
struct node
{
    int num;
    int fail;
    int next[4];
    void init()
    {
        memset(next,-1,sizeof(next));
        fail=-1;
        num=0;
    }
}a[1000];
inline int get_num(char c)
{
    if(c=='A')return 0;
    if(c=='C')return 1;
    if(c=='G')return 2;
    return 3;
}
void insert(char s[])
{
    int p=1;
    for(int i=0;s[i];i++)
    {
    int num=get_num(s[i]);
    if(a[p].next[num]==-1)
    {
        a[cnt].init();
        a[p].next[num]=cnt++;
    }
    p=a[p].next[num];
    }
    a[p].num++;
}
void bfs_ac()
{
    queue<int>q;
    for(int i=0;i<4;i++)
    a[0].next[i]=1;
    a[1].fail=0;
    q.push(1);
    while(!q.empty())
    {
    int p=q.front();q.pop();
    for(int i=0;i<4;i++)
    {
        if(a[p].next[i]!=-1)
        {
        a[a[p].next[i]].fail=a[a[p].fail].next[i];
        a[a[p].next[i]].num+=a[a[a[p].fail].next[i]].num;
        q.push(a[p].next[i]);     
        }
        else
        {
        a[p].next[i]=a[a[p].fail].next[i];
        }
    }
    }
}
int main()
{
    int i,j,V=1;
    char s[50];
    while(scanf("%d",&n)&&n)
    {
    cnt=2;
    a[0].init();a[1].init();
    for(i=1;i<=n;i++)
    {
        scanf("%s",s);
        insert(s);
    }
    scanf("%s",s);
    memset(num,0,sizeof(num));
    for(i=0;s[i];i++)
    {
        num[get_num(s[i])]++;
    }
    bfs_ac();
    int A,B,C,D,sum;
    bin[0]=(num[1]+1)*(num[2]+1)*(num[3]+1);
    bin[1]=(num[2]+1)*(num[3]+1);
    bin[2]=(num[3]+1);
    bin[3]=1;
    sum=bin[0]*num[0]+bin[1]*num[1]+bin[2]*num[2]+bin[3]*num[3];
    for(i=0;i<cnt;i++)
        for(j=0;j<=sum;j++)
        dp[i][j]=-1;
    dp[1][0]=0;
    for(A=0;A<=num[0];A++)
    {
        for(B=0;B<=num[1];B++)
        {
        for(C=0;C<=num[2];C++)
        {
            for(D=0;D<=num[3];D++)
            {
            sum=bin[0]*A+bin[1]*B+bin[2]*C+bin[3]*D;
            for(i=0;i<cnt;i++)
            {
                if(A>=1&&dp[i][sum-bin[0]]!=-1)
                dp[a[i].next[0]][sum]=max(dp[a[i].next[0]][sum],dp[i][sum-bin[0]]+a[a[i].next[0]].num);
                if(B>=1&&dp[i][sum-bin[1]]!=-1)
                dp[a[i].next[1]][sum]=max(dp[a[i].next[1]][sum],dp[i][sum-bin[1]]+a[a[i].next[1]].num);
                if(C>=1&&dp[i][sum-bin[2]]!=-1)
                dp[a[i].next[2]][sum]=max(dp[a[i].next[2]][sum],dp[i][sum-bin[2]]+a[a[i].next[2]].num);
                if(D>=1&&dp[i][sum-bin[3]]!=-1)
                dp[a[i].next[3]][sum]=max(dp[a[i].next[3]][sum],dp[i][sum-bin[3]]+a[a[i].next[3]].num);
            }
            }
        }
        }
    }
    int ans=0;
    int tmp=num[0]*bin[0]+num[1]*bin[1]+num[2]*bin[2]+num[3]*bin[3];
    for(i=0;i<cnt;i++)if(dp[i][tmp]!=-1)
        ans=ans>dp[i][tmp]?ans:dp[i][tmp];
    printf("Case %d: %d\n",V++,ans);
    }
}
