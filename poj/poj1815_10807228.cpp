#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
#define VM 1500
#define EM 20550
#define inf 0x3f3f3f3f


int s,t,m;
int u[EM],v[EM],cap[EM],ncnt;
int ans[VM],cnt,vis[EM];
inline void addback(int x,int y,int c)
{
	u[ncnt]=x;
	v[ncnt]=y;
	cap[ncnt++]=c;
}
#define MAXN 1122  
#define MAXM 222222  
#define INF 1000000000  
using namespace std;  
struct node  
{

	int ver;    // vertex  
	int cap;    // capacity  
	int flow;   // current flow in this arc  
	int next, rev;  
}edge[MAXM];  
int dist[MAXN], numbs[MAXN], src, des, n;  
int head[MAXN], e;  
void addedge(int x, int y, int c)  
{
	addback(x,y,c);
	//printf("%d	-> %d:	%d\n",x,y,c);
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
rev_BFS();
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
	//freopen("out.txt","w",stdout);
#endif
	while(scanf("%d %d %d",&m,&s,&t)==3)
	{
		ncnt=0;
		init();
		for(int i=1;i<=m;i++)
		{
			if(i==s)
			{
				addedge(s,s+m,INF);
				continue;
			}
			if(i==t)
			{
				addedge(t,t+m,INF);
				continue;
			}
			addedge(i,i+m,1);
		}
		bool noans=false;
		for(int i=1;i<=m;i++)
			for(int j=1;j<=m;j++)
			{
				int tmp;
				scanf("%d",&tmp);
				if(i==j)
					continue;
				if(tmp==1)
				{
					if(i==s && j==t)
						noans=true;
					if(i!=t && j!=s)
						addedge(i+m,j,INF);
				}
			}
		if(s==t || noans)
		{
			puts("NO ANSWER!");
			continue;
		}
		n=m*2+2;
		t=t+m;
		src=s;
		des=t;
		int maxf=maxflow();

		printf("%d\n",maxf);
		if(maxf==0)
			continue;

		cnt=0;
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=m;i++)
		{
			if(i==s || i==t-m)
				continue;

			init();
			int pos;
			for(int j=0;j<ncnt;j++)
			{
				if(vis[j])
				{
//					addedge(u[j],v[j],0);
//					ncnt--;
					continue;
				}
				if(u[j]==i && v[j]==i+m)
				{
					pos=j;
//					addedge(i,i+m,0);
//					ncnt--;
					continue;
				}
				addedge(u[j],v[j],cap[j]);
				ncnt--;
			}
			int tmpf=maxflow();
//			printf("*%d        %d\n",i,tmpf);
			if(tmpf==maxf-1)
			{
				maxf--;
				vis[pos]=1;
				ans[cnt++]=i;
			}
		}
		//		printf("%d	*****\n",cnt);
		for(int i=0;i<cnt;i++)
		{
			if(i)printf(" ");
			printf("%d",ans[i]);
		}
		puts("");
	}
	return 0;
}
