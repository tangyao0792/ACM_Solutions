/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>
#define max(a,b) (a>b?a:b)

const int MAXN=1111;
const int size=26;
const int INF=1<<29;

struct Node
{
    int next[size];
    int fail,cnt;
    int ch;
    void init()
    {
        cnt=fail=0;
        ch=0;
        memset(next,0,sizeof(next));
    }
}node[MAXN];

int cnt;        //・&#214;&#197;&#228;&#189;úμ&#227;
int n,m;
int queue[MAXN],head,tail;
int w[111];
int dp[55][1111];
int fa[55][1111];

char word[111][55];

void insert(char *str,int w)
{
    int pos=0;
    int nlen=strlen(str);
    for(int i=nlen-1;i>=0;i--)
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
    node[pos].cnt+=w;
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
        //        if(node[fail].cnt)        //°üo&#172;
        //            node[cur].cnt=1;

        node[cur].cnt+=node[fail].cnt;

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
}

bool check(int a,int b,int pl)
{
    while(pl>=0)
    {
        if(node[a].ch<node[b].ch)    return false;
        if(node[a].ch>node[b].ch)    return true;
        a=fa[pl][a];
        b=fa[pl][b];
        pl--;
    }
    return true;
}

void solve()
{
    make_fail();
    for(int i=0;i<=n;i++)
        for(int j=0;j<=cnt;j++)
            dp[i][j]=-INF;
    memset(fa,0,sizeof(fa));
    dp[0][0]=0;


    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=cnt;j++)
        {
            for(int k=0;k<size;k++)
            {
                int next=node[j].next[k];
                int tmp=node[next].cnt;
                if(dp[i][next]<dp[i-1][j]+tmp || (dp[i][next]==dp[i-1][j]+tmp && node[fa[i][next]].ch>node[j].ch))
                {
                    dp[i][next]=dp[i-1][j]+tmp;
                    fa[i][next]=j;
                }
            }
        }
        for(int j=0;j<=cnt;j++)
        {
            int fail=node[j].fail;
            if(dp[i][j]>dp[i][fail] || (node[fa[i][j]].ch<node[fa[i][fail]].ch && dp[i][j]==dp[i][fail]))
            {
                dp[i][fail]=dp[i][j];
                fa[i][fail]=fa[i][j];
            }
        }
    }
//    for(int i=1;i<=n;i++)
//    {
//        for(int j=0;j<=cnt;j++)
//        {
//            for(int k=0;k<26;k++)
//            {
//                int next=node[j].next[k];
//                if(dp[i-1][j]+node[next].cnt > dp[i][next] ||
//                        (dp[i-1][j]+node[next].cnt==dp[i][next] &&
//                        node[fa[i][next]].ch>node[j].ch))
//                {
//
//                    dp[i][next]=dp[i-1][j]+node[next].cnt;
//                    fa[i][next]=j;
//
//                }
//            }
//        }
//        for(int j=0;j<=cnt;j++)
//        {
//            int fail=node[j].fail;
//            if(dp[i][fail]<dp[i][j] ||
//             (dp[i][fail]==dp[i][j] &&
//                  node[fa[i][fail]].ch>node[fa[i][j]].ch))
//            {
//                dp[i][fail]=dp[i][j];
//                fa[i][fail]=fa[i][j];
//            }
//        }

//    }
    int ans=-INF;
    int pl=-1;
    for(int i=0;i<=n;i++)
        for(int j=0;j<=cnt;j++)
        {
            if(dp[i][j]>ans)
            {
                ans=dp[i][j];
                pl=i;
            }
        }

    int p=-1;
    for(int i=0;i<=cnt;i++)
    {
        if(dp[pl][i]==ans && (p==-1 || check(p,i,pl)))
            p=i;
    }
//    printf("****%d\n",ans);
    for(int i=pl;i>0;i--)
    {
        printf("%c",char(node[p].ch+int('a')));
        p=fa[i][p];
    }
    puts("");


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
        scanf("%d %d",&n,&m);
        cnt=0;
        node[cnt].init();
        node[cnt].ch=INF;
        for(int i=0;i<m;i++)
            scanf("%s",word[i]);

        for(int i=0;i<m;i++)
            scanf("%d",&w[i]);

        for(int i=0;i<m;i++)
            insert(word[i],w[i]);
        solve();
    }
    return 0;
}
