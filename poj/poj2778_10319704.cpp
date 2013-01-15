#include<cstdio>
#include<cstring>

const int MOD =100000;

struct Node
{
    int next[4];
    int fail,cnt;
    void init()
    {
        cnt=fail=next[0]=next[1]=next[2]=next[3]=0;
    }
}node[150];

int cnt;        //分配节点
int n,m;
int queue[150],head,tail;
int hash[150];      //hash[i]表示第i个节点是第几状态
int map[256];

long long a[120][120],b[120][120],c[120][120];

void insert(char *str)
{
    int pos=0;
    for(int i=0;str[i];i++)
    {
        int x=map[str[i]];
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
    for(int i=0;i<4;i++)
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
        if(node[fail].cnt)
        {
            node[cur].cnt=1;
        }
        for(int i=0;i<4;i++)
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

    int nst=0;      //状态数

    for(int i=0;i<=cnt;i++)
    {
        if(!node[i].cnt)
        {
            hash[i]=nst++;
        }
    }

    memset(b,0,sizeof(b));
    for(int i=0;i<=cnt;i++)
    {
        if(node[i].cnt)
        {
            continue;
        }
        for(int j=0;j<4;j++)
        {
            int tmp=node[i].next[j];
            if(!node[tmp].cnt)
            {
                b[hash[i]][hash[tmp]]++;
            }
        }
    }
    cnt=nst-1;          //cnt是全局变量。。
}

void multiply(long long a[120][120],long long b[120][120])  //a=a*b
{
    memset(c,0,sizeof(c));

    for(int i=0;i<=cnt;i++)
    {
        for(int j=0;j<=cnt;j++)
        {
            for(int k=0;k<=cnt;k++)
            {
                c[i][j]+=a[i][k]*b[k][j];
            }
        }
    }

    for(int i=0;i<=cnt;i++)
    {
        for(int j=0;j<=cnt;j++)
        {
            a[i][j]=c[i][j]%MOD;
        }
    }

}

int solve()
{
    make_fail();

    memset(a,0,sizeof(a));
    a[0][0]=1;

    while(n)
    {
        if(n&1)
        {
            multiply(a,b);
        }
        multiply(b,b);
        n=n>>1;
    }

    int ans=0;
    for(int i=0;i<=cnt;i++) ans+=a[0][i];

    return ans%MOD;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    memset(map,0,sizeof(map));
    map['A']=0;map['C']=1;map['T']=2;map['G']=3;

    while(scanf("%d %d",&m,&n)==2)
    {
        cnt=0;
        node[cnt].init();
        for(int i=0;i<m;i++)
        {
            char str[100];
            scanf("%s",str);
            insert(str);
        }
        printf("%d\n",solve());
    }

    return 0;
}
