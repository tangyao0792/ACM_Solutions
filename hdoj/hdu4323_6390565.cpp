/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

#define max(a,b) (a>b?a:b)

const int SIZE=31;            //number of sons
const int MAXN=1510;            //number of nodes
const int MAXL=20;            //length of a string

int cnt;        //init(): cnt=0;
int root;
int n,m;

struct NODE
{
    int next[SIZE];
    char str[MAXL];
    void init(char *p)
    {
        strcpy(str,p);
        memset(next,0,sizeof(next));
    }
}node[MAXN];

char word[MAXN][MAXL];

int dp[MAXL][MAXL];
inline int min(int a,int b,int c)
{
    int t=(a<b?a:b);
    return t<c?t:c;
}
int getEditDistance(char *s1,char *s2)        //change s1 to s2
{
    memset(dp,0,sizeof(dp));
    int len1=strlen(s1);
    int len2=strlen(s2);
    for(int i=0;i<=len1;i++)
        dp[i][0]=i;
    for(int i=0;i<=len2;i++)
        dp[0][i]=i;

    for(int i=1;i<=len1;i++)
        for(int j=1;j<=len2;j++)
        {
            int cost=(s1[i-1]==s2[j-1]?0:1);
            int insertion=dp[i][j-1]+1;
            int deletion=dp[i-1][j]+1;
            int exchange=dp[i-1][j-1]+cost;
            dp[i][j]=min(insertion,deletion,exchange);
        }
    return dp[len1][len2];
}

void insert(char *p)
{
    int dis=getEditDistance(node[root].str,p);
    int pos=root;
    while(node[pos].next[dis])
    {
        pos=node[pos].next[dis];
        dis=getEditDistance(node[pos].str,p);
        if(dis==0)    return;        //the string has already in the tree
    }
    node[pos].next[dis]=cnt++;
    node[cnt-1].init(p);
}

int find(char *p,int k,int r)        //find strings that distance <=k
{
    int dis=getEditDistance(node[r].str,p);
    int ans=0;
    for(int i=max(1,dis-k);i<=dis+k;i++)
    {
        if(node[r].next[i])
            ans+=find(p,k,node[r].next[i]);
    }
    if(dis<=k)
        ans++;
    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    int t;
    scanf("%d",&t);
    int nCase=0;
    while(t--)
    {
        scanf("%d %d",&n,&m);
        for(int i=0;i<n;i++)
            scanf("%s",word[i]);
        cnt=root=1;
        node[cnt++].init(word[0]);
        for(int i=1;i<n;i++)
            insert(word[i]);
        char tmp[MAXL];
        int k;
        printf("Case #%d:\n",++nCase);
        for(int i=0;i<m;i++)
        {
            scanf("%s %d",tmp,&k);
            printf("%d\n",find(tmp,k,root));
        }
    }
    return 0;
}
