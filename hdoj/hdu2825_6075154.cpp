/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

const int MAXN=110;
const int MOD =20090717;

struct Node
{
    int next[26];
    int fail;
    void init()
    {
        fail=0;
        memset(next,0,sizeof(next));
    }
}node[MAXN];

int cnt;        //分配节点
int n,m,k;
int queue[MAXN],head,tail;
int hash[MAXN];
int dp[26][MAXN][10+(1<<11)];
int num[1<<11];

void insert(char *str,int id)
{
    int pos=0;
    for(int i=0;str[i];i++)
    {
        int x=str[i]-'a';
        if(!node[pos].next[x])
        {
            node[++cnt].init();
            node[pos].next[x]=cnt;
        }
        pos=node[pos].next[x];
    }
    hash[pos]|=(1<<id);
}

void make_fail()
{
    head=tail=0;
    for(int i=0;i<26;i++)
    {
        if(node[0].next[i])
        {
            queue[tail++]=node[0].next[i];
            node[node[0].next[i]].fail=0;
        }
    }

    while(head<tail)
    {
        int cur=queue[head++];
        int fail=node[cur].fail;
        hash[cur]|=hash[fail];
        for(int i=0;i<26;i++)
        {
            if(node[cur].next[i])
            {
                queue[tail++]=node[cur].next[i];
                node[node[cur].next[i]].fail=node[fail].next[i];
            }
            else
            {
                node[cur].next[i]=node[fail].next[i];
            }
        }
    }

}


int solve()
{
    make_fail();

    int tmp=1<<(m);
    for(int i=0;i<=n;i++)
        for(int j=0;j<=cnt;j++)
            for(int s=0;s<tmp;s++)
                dp[i][j][s]=0;

    dp[0][0][0]=1;
    for(int i=0;i<n;i++)
    for(int j=0;j<=cnt;j++)
    for(int t=0;t<tmp;t++)
    {
        if(dp[i][j][t]==0)  continue;
        for(int v=0;v<26;v++)
        {
            int w=node[j].next[v];//自动机的下一个位置
            int h=hash[node[j].next[v]];//自动机当前包含的串集合
            dp[i+1][w][(t|h)]=(dp[i+1][w][(t|h)]+dp[i][j][t]);
            if(dp[i+1][w][(t|h)]>=MOD)
                dp[i+1][w][(t|h)]%=MOD;
        }

    }
    int ans=0;
    for(int i=0;i<=cnt;i++)
        for(int j=0;j<tmp;j++)
        {
            if(num[j]>=k)
                ans+=dp[n][i][j];
            if(ans>=MOD)    ans%=MOD;
        }
    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    num[0]=0;
    for(int i=1;i<(1<<11);i++) num[i]=num[i>>1]+(i&1);

    while(scanf("%d %d %d",&n,&m,&k)==3)
    {
        if(!n && !m && !k)  break;
        cnt=0;
        node[cnt].init();
        memset(hash,0,sizeof(hash));

        for(int i=0;i<m;i++)
        {
            char str[100];
            scanf("%s",str);
            insert(str,i);
        }
        printf("%d\n",solve());
    }

    return 0;
}
