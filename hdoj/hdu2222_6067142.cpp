/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

const int MAXN=50*10001;

struct Node
{
    int next[26];
    int fail,cnt;
    void init()
    {
        cnt=fail=0;
        memset(next,0,sizeof(next));
    }
}node[MAXN];

int n,cnt;
int queue[MAXN],head,tail;


void insert(char *str)
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
    node[pos].cnt++;
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

int find(char *str)
{
    int ans=0;
    int pos=0;
    int x;
    for(int i=0;str[i];i++)
    {
        x=str[i]-'a';
        pos=node[pos].next[x];
        int tmp=pos;
        while(tmp && node[tmp].cnt!=-1)
        {
            ans+=node[tmp].cnt;
            node[tmp].cnt=-1;
            tmp=node[tmp].fail;
        }
    }
    return ans;
}


int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    int t;
    scanf("%d",&t);
    while(t--)
    {
        cnt=0;
        node[cnt].init();
        char str[1000010];
        scanf("%d",&n);
        for(int i=0;i<n;i++)
        {
            scanf("%s",str);
            insert(str);
        }
        make_fail();
        scanf("%s",str);
        printf("%d\n",find(str));
    }
    return 0;
}
