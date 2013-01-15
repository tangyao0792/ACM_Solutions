#include<cstdio>
#include<cstring>

const int MAXN=10001;
const int MAXM=10001;

int first[MAXN],p[MAXN],anc[MAXN],d[MAXN];
int next[MAXM],u[MAXM],v[MAXM];
int n,cnt,a,b;
bool color[MAXN];

int find(int x){return p[x]==x?x:(p[x]=find(p[x]));}

void unionp(int x, int y)
{
	int px=find(x);
	int py=find(y);
	if(px!=py)
	{
		p[px]=p[py];
	}
}
bool flag;
void lca(int parent)
{color[parent]=true;
	p[parent]=parent;
	anc[find(parent)]=parent;
	for(int e=first[parent];e!=-1;e=next[e])
	{
		lca(v[e]);
		unionp(parent,v[e]);
		anc[find(v[e])]=parent;
	}

    if(flag)    return;
	if(parent==a && color[b])
	{
		printf("%d\n",anc[find(b)]);
		flag=true;
	}
	else if(parent==b && color[a])
	{
		printf("%d\n",anc[find(a)]);
		flag=true;
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
#endif
	int nCase;
	scanf("%d",&nCase);
	while(nCase--)
	{
		memset(first,-1,sizeof(first));
		memset(color,0,sizeof(color));
		memset(d,0,sizeof(d));
		scanf("%d",&n);
		cnt=0;
		for(int i=1;i<n;i++)
		{
			int x,y;
			scanf("%d %d",&x,&y);
			u[cnt]=x;
			v[cnt]=y;
			d[y]++;
			next[cnt]=first[x];
			first[x]=cnt++;
		}
		scanf("%d %d",&a,&b);
		for(int i=1;i<=n;i++)
            if(!d[i])
            {
                flag=false;
                lca(i);
                break;
            }
	}
	return 0;
}
