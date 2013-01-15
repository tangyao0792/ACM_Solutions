#include<cstdio>
#include<cstring>

const int MAXN=100010;

int first[MAXN],v[MAXN],next[MAXN],w[MAXN];
int cnt;
int id[MAXN],num;
int n;
int val[MAXN];

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

void dfs(int root,int cur)
{
	val[root]=cur;
	for(int e=first[root];e!=-1;e=next[e])
	{
		int son=v[e];
		dfs(son,cur^w[e]);
	}
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
		num=1;
		memset(first,-1,sizeof(first));
		memset(id,0,sizeof(id));

		int x,y,wi;
		int root=1;
		for(int i=0;i<n-1;i++)
		{
			scanf("%d %d %d",&x,&y,&wi);
			if(num==1)
				root=x;
			if(!id[x])	id[x]=num++;
			if(!id[y])	id[y]=num++;
			if(id[x]>id[y])
				swap(x,y);
			addedge(x,y,wi);
		}
		dfs(root,0);

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
