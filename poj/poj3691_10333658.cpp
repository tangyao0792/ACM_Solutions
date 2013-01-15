#include<cstdio>
#include<cstring>

#define min(a,b) (a<b?a:b)

const int INF=1<<28;
const int MAXN=1010;
const int size=4;

struct Node
{
    int next[size];
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
int dp[MAXN][MAXN];
int map[300];
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
            node[cnt].ch=str[i]-'A';
        }
        pos=node[pos].next[x];
    }
    node[pos].cnt++;
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

inline char getch(int x)
{
    switch (x)
    {
        case 0:return 'A';
        case 1:return 'T';
        case 2:return 'G';

    }
    return 'C';
}

int solve(char *str)
{
	make_fail();
	int nLen=strlen(str);
	for(int i=0;i<=nLen;i++)
		for(int j=0;j<=cnt;j++)
			dp[i][j]=INF;
	dp[0][0]=0;
	int w;
	for(int i=0;i<nLen;i++)
	{
		for(int j=0;j<=cnt;j++)
		{
			if(node[j].cnt)continue;
			for(int k=0;k<size;k++)
			{
				int next=node[j].next[k];
                if(node[next].cnt)	continue;
				char c=getch(k);
				if(str[i]!=c)
					w=1;
				else
					w=0;

				dp[i+1][next]=min(dp[i+1][next],dp[i][j]+w);
			}
		}
	}
	int ans=INF;
	for(int i=0;i<=cnt;i++)
		ans=min(ans,dp[nLen][i]);
	return ans;
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	map['A']=0;map['T']=1;
	map['G']=2;map['C']=3;
	int nCase=0;
	while(scanf("%d",&n)==1 && n)
	{
		nCase++;
		char str[1100];
		cnt=0;
		node[cnt].init();
		node[cnt].ch='Z'-'A';
		for(int i=0;i<n;i++)
		{
			scanf("%s",str);
			insert(str);
		}
		scanf("%s",str);
		int ans=solve(str);
		if(ans==INF)
			ans=-1;
		printf("Case %d: %d\n",nCase,ans);
	}
	return 0;
}
