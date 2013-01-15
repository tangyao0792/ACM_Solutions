#include<cstdio>
#include<cstring>

#define MAXN 300
#define inf 1000000000

int mat[MAXN][MAXN],flow[MAXN][MAXN];
int n,m;

int max_flow(int n,int mat[][MAXN],int source,int sink,int flow[][MAXN])
{

	int pre[MAXN],que[MAXN],d[MAXN],p,q,t,i,j;
	if (source==sink) return inf;
	for (i=0;i<n;i++)
		for (j=0;j<n;flow[i][j++]=0);
	for (;;){

		for (i=0;i<n;pre[i++]=0);
		pre[t=source]=source+1,d[t]=inf;
		for (p=q=0;p<=q&&!pre[sink];t=que[p++])
			for (i=0;i<n;i++)
				if (!pre[i]&&(j=mat[t][i]-flow[t][i]))
				{
					que[q++]=i;
					pre[i]=t+1,d[i]=(d[t]<j?d[t]:j);
				}
				else if (!pre[i]&&(j=flow[i][t]))
					pre[que[q++]=i]=-t-1,d[i]=(d[t]<j?d[t]:j);
		if (!pre[sink]) break;
		for (i=sink;i!=source;)
			if (pre[i]>0)
				flow[pre[i]-1][i]+=d[sink],i=pre[i]-1;
			else
				flow[i][-pre[i]-1]-=d[sink],i=-pre[i]-1;
	}
	for (j=i=0;i<n; j+=flow[source][i++]);
	return j;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while(scanf("%d %d",&m,&n)==2)
	{
		memset(mat,0,sizeof(mat));
		for(int i=0;i<m;i++)
		{
			int x,y,w;
			scanf("%d %d %d",&x,&y,&w);
			x--;y--;
			mat[x][y]+=w;
		}
		printf("%d\n",max_flow(n,mat,0,n-1,flow));
	}

	return 0;
}
