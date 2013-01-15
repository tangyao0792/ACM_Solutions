#include<cstdio>
#include<cstring>
#include<queue>
#include<iostream>
#include<vector>

using namespace std;

//最大流

const int MAXN=300;
const int INF=1<<29;

int g[MAXN][MAXN];

//0...n-1
// init:ne=2 head = 0
const int N=333;
const int E=200*33*2;

#define typec int
const typec inf = 0x3f3f3f3f;

struct edge
{


	int x, y, nxt; typec c;
}bf[E];
int ne, head[N], cur[N], ps[N], dep[N];
int n,m;
void addedge(int x, int y, typec c)
{

	// add an arc(x -> y, c); vertex: 0 ~ n-1;
	bf[ne].x = x; bf[ne].y = y; bf[ne].c = c;
	bf[ne].nxt = head[x]; head[x] = ne++;
	bf[ne].x = y; bf[ne].y = x; bf[ne].c = 0;
	bf[ne].nxt = head[y]; head[y] = ne++;
}
typec flow(int n, int s, int t)
{

	typec tr, res = 0;
	int i, j, k, f, r, top;
	while (1) {

		memset(dep, -1, n * sizeof(int));
		for (f = dep[ps[0] = s] = 0, r = 1; f != r; )
			for (i = ps[f++], j = head[i]; j; j = bf[j].nxt)
			{

				if (bf[j].c && -1 == dep[k = bf[j].y]){

					dep[k] = dep[i] + 1; ps[r++] = k;
					if (k == t) {
						f = r; break; }
				}
			}
		if (-1 == dep[t]) break;
		memcpy(cur, head, n * sizeof(int));
		for (i = s, top = 0; ; ) {
			if (i == t) {
				for (k = 0, tr = inf; k < top; ++k)
					if (bf[ps[k]].c < tr)
						tr = bf[ps[f = k]].c;
				for (k = 0; k < top; ++k)
					bf[ps[k]].c -= tr, bf[ps[k]^1].c += tr;
				res += tr; i = bf[ps[top = f]].x;
			}
			for (j=cur[i]; cur[i]; j = cur[i] = bf[cur[i]].nxt)
				if (bf[j].c && dep[i]+1 == dep[bf[j].y]) break;
			if (cur[i]) {

				ps[top++] = cur[i];
				i = bf[cur[i]].y;
			}
			else {

				if (0 == top) break;
				dep[i] = -1; i = bf[ps[--top]].x;
			}
		}
	}
	return res;
}

void make(int k,int c,int m,int limit)
{
	ne=2;
	memset(head,0,sizeof(head));
	for(int i=1;i<=k;i++)
		for(int j=k+1;j<=k+c;j++)
		{
			if(g[i][j]<=limit)
			{
				addedge(j,i,1);
			}
		}
	for(int i=1;i<=k;i++)
		addedge(i,0,m);
	for(int i=k+1;i<=k+c;i++)
		addedge(k+c+1,i,1);
}

int solve(int k,int c,int m, int r)
{
	int l=1;
	while(l<=r)
	{
		int mid=(l+r)/2;
		make(k,c,m,mid);
		int tmp=flow(k+c+2,k+c+1,0);

		if(tmp==c)
			r=mid-1;
		else
			l=mid+1;
	}
	return l;
}

void floyd(int n)
{
	for(int k=0;k<n;k++)
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				if(g[i][j]>g[i][k]+g[k][j])
					g[i][j]=g[i][k]+g[k][j];
}



int main(int argc, const char *argv[])
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	int k,c,m;
	while(scanf("%d %d %d",&k,&c,&m)==3)
	{
		int sum=0;
		for(int i=0;i<=k+c+2;i++)
			for(int j=0;j<=k+c+2;j++)
				g[i][j]=INF;
		for(int i=1;i<=k+c;i++)
			for(int j=1;j<=k+c;j++)
			{
				scanf("%d",&g[i][j]);
				sum+=g[i][j];
				if(g[i][j]==0)
					g[i][j]=INF;
			}
		for(int i=1;i<=k;i++)
		{
			g[i][0]=0;
		}

		for(int i=k+1;i<=k+c;i++)
		{
			g[k+c+1][i]=0;
		}

		floyd(k+c+2);

		printf("%d\n",solve(k,c,m,sum));
	}
	return 0;
}
