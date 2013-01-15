#include<cstdio>
#include<cstring>

#define min(a,b) (a<b?a:b)

const int INF=1<<29;
#define MAXN 222
#define MAXM 222*222*2

using namespace std;
struct node
{
	int ver;    // vertex
	int cap;    // capacity
	int flow;   // current flow in this arc
	int next, rev;
}edge[MAXM];
int dist[MAXN], numbs[MAXN], src, des, n,m;
int head[MAXN], e;
int u[MAXM],v[MAXM],cap[MAXM],ncnt;

inline void addback(int x,int y,int c)
{
	u[ncnt]=x;
	v[ncnt]=y;
	cap[ncnt++]=c;
}

inline void add(int x, int y, int c,int f=0)
{
	if(!f)
		addback(x,y,c);
	//e记录边的总数
	edge[e].ver = y;
	edge[e].cap = c;
	edge[e].flow = 0;
	edge[e].rev = e + 1;        //反向边在edge中的下标位置
	edge[e].next = head[x];   //记录以x为起点的上一条边在edge中的下标位置
	head[x] = e++;           //以x为起点的边的位置
	//反向边
	edge[e].ver = x;
	edge[e].cap = 0;  //反向边的初始网络流为0
	edge[e].flow = 0;
	edge[e].rev = e - 1;
	edge[e].next = head[y];
	head[y] = e++;
}
void rev_BFS()
{
	int Q[MAXN], qhead = 0, qtail = 0;
	for(int i = 1; i <= n; ++i)
	{

		dist[i] = MAXN;
		numbs[i] = 0;
	}
	Q[qtail++] = des;
	dist[des] = 0;
	numbs[0] = 1;
	while(qhead != qtail)
	{
		int v = Q[qhead++];
		for(int i = head[v]; i != -1; i = edge[i].next)
		{

			if(edge[edge[i].rev].cap == 0 || dist[edge[i].ver] < MAXN)continue;
			dist[edge[i].ver] = dist[v] + 1;
			++numbs[dist[edge[i].ver]];
			Q[qtail++] = edge[i].ver;
		}
	}
}
void init()
{
	e = 0;
	memset(head, -1, sizeof(head));
}
int maxflow()
{

	rev_BFS() ;
	int u, totalflow = 0;
	int Curhead[MAXN], revpath[MAXN];
	for(int i = 1; i <= n; ++i)Curhead[i] = head[i];
	u = src;
	while(dist[src] < n)
	{

		if(u == des)     // find an augmenting path
		{

			int augflow = INF;
			for(int i = src; i != des; i = edge[Curhead[i]].ver)
				augflow = min(augflow, edge[Curhead[i]].cap);
			for(int i = src; i != des; i = edge[Curhead[i]].ver)
			{

				edge[Curhead[i]].cap -= augflow;
				edge[edge[Curhead[i]].rev].cap += augflow;
				edge[Curhead[i]].flow += augflow;
				edge[edge[Curhead[i]].rev].flow -= augflow;
			}
			totalflow += augflow;
			u = src;
		}
		int i;
		for(i = Curhead[u]; i != -1; i = edge[i].next)
			if(edge[i].cap > 0 && dist[u] == dist[edge[i].ver] + 1)break;
		if(i != -1)     // find an admissible arc, then Advance
		{

			Curhead[u] = i;
			revpath[edge[i].ver] = edge[i].rev;
			u = edge[i].ver;
		}
		else        // no admissible arc, then relabel this vertex
		{

			if(0 == (--numbs[dist[u]]))break;    // GAP cut, Important!
			Curhead[u] = head[u];
			int mindist = n;
			for(int j = head[u]; j != -1; j = edge[j].next)
				if(edge[j].cap > 0)mindist = min(mindist, dist[edge[j].ver]);
			dist[u] = mindist + 1;
			++numbs[dist[u]];
			if(u != src)
				u = edge[revpath[u]].ver;    // Backtrack
		}
	}
	return totalflow;
}
int g[MAXN][MAXN];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("f.in","r",stdin);
#endif
	while(scanf("%d %d",&n,&m)==2)
	{
//		printf("%d	%d\n",n,m);
        memset(g,0,sizeof(g));
		ncnt=0;
		init();
		for(int i=1;i<=n;i++)
		{
			add(i,i+n,1);
		}
		char str[22];
		for(int i=0;i<m;i++)
		{
			scanf("%s",str);
			int x,y;
//			scanf(" (%d,%d)",&x,&y);
			sscanf(str,"(%d,%d)",&x,&y);
			x++,y++;
			g[x][y]=1;
			g[y][x]=1;
//			printf("%d	->	%d\n",x,y);
			add(x+n,y,INF);
			add(y+n,x,INF);
		}
		int ans=INF;
		int size=n;
		n=n*2+2;


		for(int i=1;i<=size;i++)
			for(int j=i+1;j<=size;j++)
			{
				if(g[i][j]) continue;
				init();
				for(int k=0;k<ncnt;k++)
				{
					add(u[k],v[k],cap[k],1);
				}

				src=i+size;
				des=j;
//				puts("1");
				int tmp=maxflow();
//				printf("%d	->	%d:	%d\n",i,j,tmp);
				ans=min(ans,tmp);
			}
		if(ans>size)
			ans=size;
		printf("%d\n",ans);

	}
	return 0;
}
