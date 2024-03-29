#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;

inline int ABS(int x)
{
	return x>0?x:(-x);
}

int m;
const int MAXN=	222;
const int MAXM=2222;
const int INF=1<<29;

int in[MAXN],out[MAXN],num[MAXN];

struct node
{

	int ver;    // vertex
	int cap;    // capacity
	int flow;   // current flow in this arc
	int next, rev;
}edge[MAXM];
int dist[MAXN], numbs[MAXN], src, des, n;
int head[MAXN], e;
inline void add(int x, int y, int c)
{
//    printf("%d  ->  %d  :   %d\n",x,y,c);
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
void init()
{
	memset(out,0,sizeof(out));
	memset(in,0,sizeof(in));
	e = 0;
	memset(head, -1, sizeof(head));
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

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif

	int t;
	scanf("%d",&t);
	while(t--)
	{
		init();
		scanf("%d %d",&n,&m);
		for(int i=0;i<m;i++)
		{
			int x,y,f;
			scanf("%d %d %d",&x,&y,&f);
			if(x==y)    continue;
			if(f==1)
			{
				out[x]++,in[y]++;
			}
			else
			{
				out[x]++,in[y]++;	//edge is pretend x->y
				add(y,x,1);			//y->x for maxflow
			}
		}
		bool flag=true;
		int sum=0;
		for(int i=1;i<=n;i++)
		{
			int tmp=out[i]-in[i];
			if(ABS(tmp)%2==1)
			{
				flag=false;
				break;
			}
			else
				num[i]=tmp/2;
		}
		if(!flag)
		{
			puts("impossible");
			continue;
		}
		for(int i=1;i<=n;i++)
		{
			if(num[i]>0)
			{
				add(i,n+1,num[i]);
                sum+=num[i];
			}
			else if(num[i]<0)
			{
				add(n+2,i,-num[i]);
			}
		}
		src=n+2;des=n+1;
		n+=2;
		if(sum==maxflow())
		{
			puts("possible");
		}
		else
		{
			puts("impossible");
		}
	}

	return 0;
}
