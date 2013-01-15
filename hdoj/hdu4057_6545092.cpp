/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

#define max(a,b) (a>b?a:b)

const int INF=1<<29;
const int MAXN=1010;
const int size=26;

struct Node
{
    int next[size];
    int fail,cnt;
    int w;
    void init()
    {
        w=0;
        cnt=fail=0;
        memset(next,0,sizeof(next));
    }
}node[MAXN];

int cnt;        //分配节点
int n,m;
int queue[MAXN],head,tail;
int map[300];
int w[1<<12];

int dp[2][MAXN][1<<12];

void insert(char *str,int no)
{
    int pos=0;
    for(int i=0;str[i];i++)
    {
        int x=map[int(str[i])];
        if(!node[pos].next[x])
        {
            node[++cnt].init();
            node[pos].next[x]=cnt;
        }
        pos=node[pos].next[x];
    }
    node[pos].cnt=1<<no;
}


void make_fail()
{
    head=tail=0;
    for(int i=0;i<size;i++)
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

        for(int i=0;i<size;i++)
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

    for(int i=0;i<=cnt;i++)
    {
        int pos=node[i].fail;
        while(pos)
        {
            if(node[pos].cnt!=-1)
                node[i].cnt|=node[pos].cnt;
            pos=node[pos].fail;
        }
    }

}

int solve()
{

    make_fail();
    int s=1<<m;
    for(int i=0;i<=cnt;i++)
        for(int k=0;k<s;k++)
            dp[0][i][k]=0;
    dp[0][0][0]=1;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<=cnt;j++)
            for(int k=0;k<s;k++)
                dp[(i+1)%2][j][k]=0;
        for(int j=0;j<=cnt;j++)
        {
            for(int k=0;k<s;k++)
            {
                if(!dp[i%2][j][k])  continue;
                for(int a=0;a<4;a++)
                {
                    int next=node[j].next[a];
                    int no=node[next].cnt;
                    dp[(i+1)%2][next][k|no]=1;
                }
            }
        }
    }

    int ans=-1;
    for(int j=0;j<=cnt;j++)
    {
        for(int k=0;k<s;k++)
        {
            if(!dp[n%2][j][k])  continue;
            int tmp=0;
            for(int a=0;a<m;a++)
            {
                if(k&(1<<a))
                    tmp+=w[(1<<a)];
            }
            ans=max(ans,tmp);
        }
    }
    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif


    map[int('A')]=0;
    map[int('T')]=1;
    map[int('G')]=2;
    map[int('C')]=3;
    while(scanf("%d %d",&m,&n)==2)
    {
        char str[20];
        cnt=0;
        node[cnt].init();
        for(int i=0;i<m;i++)
        {
            scanf("%s %d",str,&w[1<<i]);
            insert(str,i);
        }
        int ans=solve();
        if(ans<0)
            puts("No Rabbit after 2012!");
        else
            printf("%d\n",ans);
    }
    return 0;
}
