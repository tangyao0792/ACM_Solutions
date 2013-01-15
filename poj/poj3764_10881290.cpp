#include<cstdio>
#include<cstring>

const int MAXN=100010;

int first[MAXN],v[MAXN*2],next[MAXN*2],w[MAXN*2];
int cnt;
int n;
int val[MAXN];
struct node
{
	int fa,u;
}que[MAXN];
int front,rear;

inline void swap(int &x,int &y)
{
	int tmp=x;
	x=y;
	y=tmp;
}

inline void addedge(int fa,int son,int wi)
{
    w[cnt]=wi;
	v[cnt]=son;
	next[cnt]=first[fa];
	first[fa]=cnt++;
}


int top,tree[MAXN*32][3];

inline void insert(int s)
{
	int pos=0;
	for(int i=30;i>=0;i--)
	{
		int x=(1<<i)&s;
		x=x?1:0;
		if(tree[pos][x]==0)
		{
			tree[pos][x]=top++;
		}
		pos=tree[pos][x];
	}
	tree[pos][2]=1;
}

inline int getmax(int s)
{
	int pos=0;
	int ans=0;
	for(int i=30;i>=0;i--)
	{
		int x=(1<<i)&s;
		int bit=x?0:1;
		if(tree[pos][bit])
		{
            ans+=1<<i;
			pos=tree[pos][bit];
		}
		else
		{
			pos=tree[pos][bit^1];
		}
	}
	return ans;
}

void bfs()
{
	rear=front=0;
	val[0]=0;
	rear++;
	que[0].fa=-1;
	que[0].u=0;
	while(front<rear)
	{
		int u=que[front].u;
		int fa=que[front++].fa;
		for(int e=first[u];e!=-1;e=next[e])
		{
			int son=v[e];
			if(son==fa)	continue;
			val[son]=val[u]^w[e];
			que[rear].u=son;
			que[rear++].fa=u;
		}
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while(scanf("%d",&n)==1)
	{
		top=1;
		memset(tree,0,sizeof(tree));
		cnt=0;
		memset(first,-1,sizeof(first));

		int x,y,wi;
		for(int i=0;i<n-1;i++)
		{
			scanf("%d %d %d",&x,&y,&wi);
			addedge(x,y,wi);
			addedge(y,x,wi);
		}

		bfs();

		int ans=0;

		for(int i=0;i<n;i++)
		{
			insert(val[i]);
			int tmp=getmax(val[i]);
			if(tmp>ans)
				ans=tmp;
		}
		printf("%d\n",ans);
	}
	return 0;
}
