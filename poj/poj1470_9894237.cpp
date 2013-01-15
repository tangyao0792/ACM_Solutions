#include<cstdio>
#include<cstring>
#include<iostream>
#include<vector>

using namespace std;

const int MAXN=1000;
vector<int> adj[MAXN];
int num[MAXN],d[MAXN],p[MAXN],anc[MAXN];
int n;
bool chk[MAXN];

typedef pair<int,int> pii;
vector<pii> quest;

int find(int x){return p[x]==x?x:(p[x]=find(p[x]));}

void unionp(int x,int y)
{
	int px=find(x);
	int py=find(y);
	p[px]=py;
}

void lca(int par)
{
	p[par]=par;
	anc[find(par)]=par;
	int tmp=adj[par].size();
	for(int i=0;i<tmp;i++)
	{
		lca(adj[par][i]);
		unionp(par,adj[par][i]);
		anc[find(adj[par][i])]=par;
	}
	chk[par]=true;
	tmp=quest.size();
	
	for(int i=0;i<tmp;i++)
	{
		int x=quest[i].first;
		int y=quest[i].second;
		if(par==x && chk[y])
		{
			num[anc[find(y)]]++;
		}
		else if(par==y && chk[x])
		{
			num[anc[find(x)]]++;
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
		memset(chk,0,sizeof(chk));
		memset(d,0,sizeof(d));
		memset(num,0,sizeof(num));
		for(int i=1;i<=n;i++)
		{
			char c;int x,y,z;
			scanf("%d",&x);
			while((c=getchar())!=':');
			while((c=getchar())!='(');
			scanf("%d",&y);
			while((c=getchar())!=')');
			adj[x].clear();
			for(int j=0;j<y;j++)
			{
				scanf("%d",&z);
				d[z]++;
				adj[x].push_back(z);
			}
		}
		quest.clear();
		int q;
		cin>>q;
		char c;
		int x,y;
		while(q--)
		{
			while((c=getchar())!='(');
			scanf("%d %d",&x,&y);
			while((c=getchar())!=')');
			quest.push_back(make_pair(x,y));
		}
		for(int i=1;i<=n;i++)
		{
			if(d[i]==0)
			{
				lca(i);
				break;
			}
		}
		
		for(int i=1;i<=n;i++)
		{
			if(num[i])
				printf("%d:%d\n",i,num[i]);
		}
	}	
	return 0;
}
