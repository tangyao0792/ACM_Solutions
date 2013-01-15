#include<cstdio>
#include<cstring>

#define max(a,b) (a>b?a:b)

const int N=222;
const int E=40010*4;

int n,m,t;

#define typec int
const typec inf = 0x3f3f3f3f;

struct edge
{
	int x, y, nxt; typec c;
	int w;
}bf[E];
int ne, head[N], cur[N], ps[N], dep[N];
int cnt,first[N],v[E],next[E],we[E];
inline void insert(int x,int y,int w)
{
    v[cnt]=y;we[cnt]=w;
    next[cnt]=first[x];
    first[x]=cnt++;
}

inline void addedge(int x, int y,int w, typec c=1)
{
	// add an arc(x -> y, c); vertex: 0 ~ n-1;
	bf[ne].x = x; bf[ne].y = y; bf[ne].c = c;
	bf[ne].w=w;
	bf[ne].nxt = head[x]; head[x] = ne++;
	bf[ne].x = y; bf[ne].y = x; bf[ne].c = 0;
	bf[ne].w=w;
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
//				if(bf[j].w>l)	continue;
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
			{
//				if(bf[j].w>l)	continue;
				if (bf[j].c && dep[i]+1 == dep[bf[j].y]) break;
			}
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
void make(int l)
{
    ne=2;memset(head,0,sizeof(head));
    for(int i=0;i<n;i++)
    {
        for(int e=first[i];e!=-1;e=next[e])
        {
            if(we[e]>l)  continue;
            addedge(i,v[e],we[e]);
        }
    }
}

int solve(int r)
{
	int l=0;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		make(mid);
		int tmp=flow(n,0,n-1);
		if(tmp>=t)
			r=mid-1;
		else
			l=mid+1;
	}
	return l;
}

int main(int argc, const char *argv[])
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while(scanf("%d %d %d",&n,&m,&t)==3)
	{
		ne=2;
		cnt=0;
		memset(head,0,sizeof(head));
		memset(first,-1,sizeof(first));
		int r=0;
		for(int i=0;i<m;i++)
		{
			int x,y,w;
			scanf("%d %d %d",&x,&y,&w);
			r=max(r,w);
			x--,y--;
			insert(x,y,w);
			insert(y,x,w);
		}
		printf("%d\n",solve(r));
	}
	return 0;
}
