/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>

using namespace std;

const int MAXN=1001;
const int size=4;

struct Node
{
    int next[size];
    int fail,cnt;
    void init()
    {
        cnt=fail=next[0]=next[1]=next[2]=next[3]=0;
    }
}node[MAXN];

int cnt;        //分配节点
int n;
int dp[MAXN][20000];

inline int get_num(char c)
{
    if(c=='A')return 0;
    if(c=='T')return 1;
    if(c=='G')return 2;
    return 3;
}
void insert(char *str)
{
    int pos=0;
    for(int i=0;str[i];i++)
    {
        int x=get_num(str[i]);
        if(!node[pos].next[x])
        {
            node[++cnt].init();
            node[pos].next[x]=cnt;
        }
        pos=node[pos].next[x];
    }
    node[pos].cnt++;
}

void make_fail()
{
    queue<int> q;

    for(int i=0;i<size;i++)
    {
        if(node[0].next[i])
        {
            q.push(node[0].next[i]);
            node[node[0].next[i]].fail=0;
        }
    }
    while(!q.empty())
    {
        int cur=q.front();
        q.pop();
        int fail=node[cur].fail;

        node[cur].cnt+=node[fail].cnt;

        for(int i=0;i<size;i++)
        {
            if(node[cur].next[i])
            {
                q.push(node[cur].next[i]);
                node[node[cur].next[i]].fail=node[fail].next[i];
            }
            else
            {
                node[cur].next[i]=node[fail].next[i];
            }
        }
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif

    int nCase=1;
    while(scanf("%d",&n) && n)
    {
        cnt=0;
        node[cnt].init();
        char str[50];
        for(int i=0;i<n;i++)
        {
            scanf("%s",str);
            insert(str);
        }

        make_fail();
        scanf("%s",str);

        int num[4];
        num[0]=num[1]=num[2]=num[3]=0;
        for(int i=0;str[i];i++)
            num[get_num(str[i])]++;

        int bin[4];
        bin[0]=(num[1]+1)*(num[2]+1)*(num[3]+1);
        bin[1]=(num[2]+1)*(num[3]+1);
        bin[2]=(num[3]+1);
        bin[3]=1;
        int sum=bin[0]*num[0]+bin[1]*num[1]+bin[2]*num[2]+bin[3]*num[3];


        for(int i=0;i<=cnt;i++)
            for(int j=0;j<=sum;j++)
                dp[i][j]=-1;

        dp[0][0]=0;
        for(int a=0;a<=num[0];a++)
        for(int t=0;t<=num[1];t++)
        for(int g=0;g<=num[2];g++)
        for(int c=0;c<=num[3];c++)
        {
            int s=bin[0]*a+bin[1]*t+bin[2]*g+bin[3]*c;
            for(int i=0;i<=cnt;i++)
            {
                if(a>0 && dp[i][s-bin[0]]!=-1)
                    dp[node[i].next[0]][s]=max(dp[node[i].next[0]][s],dp[i][s-bin[0]]+node[node[i].next[0]].cnt);
                if(t>0 && dp[i][s-bin[1]]!=-1)
                    dp[node[i].next[1]][s]=max(dp[node[i].next[1]][s],dp[i][s-bin[1]]+node[node[i].next[1]].cnt);
                if(g>0 && dp[i][s-bin[2]]!=-1)
                    dp[node[i].next[2]][s]=max(dp[node[i].next[2]][s],dp[i][s-bin[2]]+node[node[i].next[2]].cnt);
                if(c>0 && dp[i][s-bin[3]]!=-1)
                    dp[node[i].next[3]][s]=max(dp[node[i].next[3]][s],dp[i][s-bin[3]]+node[node[i].next[3]].cnt);
    //            for(int j=0;j<4;j++)
    //                if(a[j]>0 && dp[i][s-bin[j]]!=-1)
    //                    dp[node[i].next[j]][s]=max(dp[node[i].next[j]][s],dp[i][s-bin[j]]+node[node[i].next[j]].cnt);
            }
        }
    int ans=0;
    int tmp=num[0]*bin[0]+num[1]*bin[1]+num[2]*bin[2]+num[3]*bin[3];
    for(int i=0;i<=cnt;i++)if(dp[i][tmp]!=-1)
        ans=ans>dp[i][tmp]?ans:dp[i][tmp];

        printf("Case %d: %d\n",nCase++,ans);
    }

    return 0;
}
