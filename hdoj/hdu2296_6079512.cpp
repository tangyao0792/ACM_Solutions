/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

#define max(a,b) (a>b?a:b)

const int INF=1<<28;
const int MAXN=1010;

struct Node
{
    int next[26];
    int fail,cnt,ch;
    void init()
    {
        cnt=fail=0;
        memset(next,0,sizeof(next));
    }
}node[MAXN];

int cnt;        //分配节点
int n,m;
int queue[MAXN],head,tail;
char word[110][20];
int val[110];
int dp[55][MAXN];
int pre[55][MAXN];

void insert(char *str,int v)
{
    int pos=0;
    int nLen=strlen(str);
    for(int i=nLen-1;i>=0;i--)
    {
        int x=str[i]-'a';
        if(!node[pos].next[x])
        {
            node[++cnt].init();
            node[pos].next[x]=cnt;
            node[cnt].ch=x;
        }
        pos=node[pos].next[x];
    }
    node[pos].cnt+=v;
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

        node[cur].cnt+=node[fail].cnt;

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
//从dp[len][a],dp[len][b]出发的字符串大小
bool comp(int len,int a,int b)
{
    if(a==-1)    return true;
    for(int i=len;i>=0;i--)
    {
        if(node[a].ch>node[b].ch)
        {
            return true;
        }
        else if(node[a].ch<node[b].ch)
        {
            return false;
        }
        a=pre[i][a];
        b=pre[i][b];
    }
    return true;
}


void solve()
{
    make_fail();
    for(int i=0;i<=n;i++)           /**************/
        for(int j=0;j<=cnt;j++)
            dp[i][j]=-INF;
    dp[0][0]=0;
    memset(pre,0,sizeof(pre));
    int len=INF,ans=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=cnt;j++)
        {
            for(int k=0;k<26;k++)
            {
                int next=node[j].next[k];
                if(dp[i-1][j]+node[next].cnt > dp[i][next] ||
                        (dp[i-1][j]+node[next].cnt==dp[i][next] &&
                        node[pre[i][next]].ch>node[j].ch))
                {

                    dp[i][next]=dp[i-1][j]+node[next].cnt;
                    pre[i][next]=j;

                }
            }
        }
        for(int j=0;j<=cnt;j++)
        {
            int fail=node[j].fail;
            if(dp[i][fail]<dp[i][j] ||
         (dp[i][fail]==dp[i][j] &&
          node[pre[i][fail]].ch>node[pre[i][j]].ch))
            {
                dp[i][fail]=dp[i][j];
                pre[i][fail]=pre[i][j];
            }
        }

    }
    for(int i=0;i<=cnt;i++)
    {
        ans=max(ans,dp[n][i]);
    }
    for(int i=0;i<=n;i++)
    {
        int tmp=0;
        for(int j=0;j<=cnt;j++)
        {
            tmp=max(tmp,dp[i][j]);
        }
        if(tmp==ans)
        {
            len=i;
            break;
        }
    }
    int from=-1;
    for(int i=0;i<=cnt;i++)
    {
        if(dp[len][i]==ans)
        {
            if(comp(len,from,i))
            {
                from=i;
            }
        }
    }

    for(int i=len;i>0;i--)
    {
        putchar('a'+node[from].ch);
        from=pre[i][from];
    }
    puts("");

}


int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    freopen("out","w",stdout);
#endif
    int t;
    scanf("%d",&t);
    while(t--)
    {

        scanf("%d %d",&n,&m);
        cnt=0;
        node[cnt].init();
        node[0].ch=INF;
        for(int i=0;i<m;i++)
        {
            scanf("%s",word[i]);
        }
        for(int i=0;i<m;i++)
        {
            scanf("%d",&val[i]);
        }
        for(int i=0;i<m;i++)
        {
            insert(word[i],val[i]);
        }
        solve();
    }

    return 0;
}
