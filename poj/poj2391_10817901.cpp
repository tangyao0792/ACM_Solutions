#include<cstdio>
#include<cstring>
#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)

const int VM = 444, EM = 444*444, INF = 0x3f3f3f3f;
const long long INFll=1ll<<60;
int m;
struct E
{
	int to,frm,nxt,cap;
}edge[EM];
int head[VM], e, n, src, des;
int dep[VM], gap[VM]; //gap[x]=y:说明残留网络中dep[i]=x的个数为y
long long g[VM][VM];

inline void init()
{
	e=0;
	memset(head,-1,sizeof(head));
}

inline void addedge(int u, int v, int c)
{
	edge[e].frm = u;edge[e].to = v;
	edge[e].cap = c;edge[e].nxt = head[u];
	head[u] = e++;
	edge[e].frm = v;edge[e].to = u;
	edge[e].cap = 0;edge[e].nxt = head[v];
	head[v] = e++;
}

void BFS(int src, int des)
{
	memset(dep, -1, sizeof(dep));
	memset(gap, 0, sizeof(gap));
	gap[0] = 1;   //说明此时有1个dep[i] = 0
	int Q[VM], front = 0, rear = 0;
	dep[des] = 0;
	Q[rear++] = des;
	int u, v;
	while (front != rear)
	{
		u = Q[front++];
		front = front%VM;
		for (int i=head[u]; i!=-1; i=edge[i].nxt)
		{
			v = edge[i].to;
			if (edge[i].cap != 0 || dep[v] != -1)
				continue;
			Q[rear++] = v;
			rear = rear % VM;
			++gap[dep[v] = dep[u] + 1];  //求出各层次的数量
		}
	}
}

int SAP(int src, int des)
{
	int res = 0;
	BFS(src, des);
	int cur[VM];
	int S[VM], top = 0;
	memcpy(cur, head, sizeof(head));
	int u = src, i;
	while (dep[src] < n)   //n为结点的个数
	{
		if (u == des)
		{
			int temp = INF, inser = n;
			for (i=0; i!=top; ++i)
				if (temp > edge[S[i]].cap)
				{
					temp = edge[S[i]].cap;
					inser = i;
				}
			for (i=0; i!=top; ++i)
			{
				edge[S[i]].cap -= temp;
				edge[S[i]^1].cap += temp;
			}
			res += temp;
			top = inser;
			u = edge[S[top]].frm;
		}
		if (u != des && gap[dep[u] -1] == 0)//出现断层，无增广路
			break;
		for (i = cur[u]; i != -1; i = edge[i].nxt)//遍历与u相连的未遍历结点
			if (edge[i].cap != 0 && dep[u] == dep[edge[i].to] + 1) //层序关系， 找到允许
				break;
		if (i != -1)//找到允许弧
		{
			cur[u] = i;
			S[top++] = i;//加入路径栈
			u = edge[i].to;//查找下一个结点
		}
		else   //无允许的路径，修改标号 当前点的标号比与之相连的点中最小的多1
		{
			int min = n;
			for (i = head[u]; i != -1; i = edge[i].nxt) //找到与u相连的v中dep[v]最小的点
			{
				if (edge[i].cap == 0)
					continue;
				if (min > dep[edge[i].to])
				{
					min = dep[edge[i].to];
					cur[u] = i;          //最小标号就是最新的允许弧
				}
			}
			--gap[dep[u]];          //dep[u] 的个数变化了 所以修改gap
			++gap[dep[u] = min + 1]; //将dep[u]设为min(dep[v]) + 1, 同时修改相应的gap[]
			if (u != src) //该点非源点&&以u开始的允许弧不存在，退点
				u = edge[S[--top]].frm;
		}
	}
	return res;
}
int in[VM],num[VM];
void floyd()
{
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(g[i][k]+g[k][j]<g[i][j])
				{
					g[i][j]=g[i][k]+g[k][j];
				}

}

long long solve(long long r,int sum)
{
    floyd();
    r=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(g[i][j]!=INFll)
                r=max(r,g[i][j]);
	long long l=0;
	long long  ans=-1;
	src=2*n+1;
	des=2*n+2;
	int size=n;
	n=n*2+2;
	while(l<=r)
	{
		long long mid=(l+r)>>1;
		init();
		for(int i=1;i<=size;i++)
		{
			addedge(src,i,in[i]);
			addedge(i+size,des,num[i]);
		}
		for(int i=1;i<=size;i++)
			for(int j=1;j<=size;j++)
			{
				if( g[i][j]<=mid)
				{
					addedge(i,j+size,INF);
				}
			}
		int tmp=SAP(src,des);
		if(tmp==sum)
		{
		    ans=mid;
			r=mid-1;
		}
		else
		{
			l=mid+1;
		}
	}
	return ans;
//	if(l>tmpr) return -1;
//	return l;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while(scanf("%d %d",&n,&m)==2)
		//    scanf("%d %d",&n,&m);
	{
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(i!=j)
					g[i][j]=INFll;
				else
					g[i][j]=0;
		int sum=0;
		long long r=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%d %d",&in[i],&num[i]);
			sum+=in[i];
		}
		for(int i=0;i<m;i++)
		{
			int x,y;
			long long l;
			scanf("%d %d %lld",&x,&y,&l);
			r+=l;
			if(g[x][y]>l)
			{
				g[x][y]=g[y][x]=l;
			}
		}
		printf("%lld\n",solve(r,sum));
	}
	return 0;
}
