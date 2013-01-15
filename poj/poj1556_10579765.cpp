#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<queue>

using namespace std;

#define typec double

const int E=555;
const int V=555;

const typec inf= 0x3f3f3f3f;
typec cost[E], dist[V];
int e, pnt[E], nxt[E], head[V], prev[V], vis[V];
int n;

#define eps 1e-6
#define zero(x) (((x)>0?(x):-(x))<eps)

struct point
{
    double x,y;
    bool operator ==(point t)const
    {
        return (t.x==x && t.y==y);
    }

};
struct line
{
	point a,b;
    bool operator != (line t)const
    {
        return !((t.a==a) && (t.b==b));
    }
}l[555],ll[555];

int cnt,ncnt;

double distances(point p1,point p2){
return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}


double xmult(point p1,point p2,point p0){
return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}


int dot_online_in(point p,line l){
return zero(xmult(p,l.a,l.b))&&(l.a.x-p.x)*(l.b.x-p.x)<eps&&(l.a.y-p.y)*(l.b.y-p.y)<eps;
}


int dots_inline(point p1,point p2,point p3){
return zero(xmult(p1,p2,p3));
}

int same_side(point p1,point p2,line l){
return xmult(l.a,p1,l.b)*xmult(l.a,p2,l.b)>eps;
}
int same_side(point p1,point p2,point l1,point l2){
return xmult(l1,p1,l2)*xmult(l1,p2,l2)>eps;
}
int dot_online_in(point p,point l1,point l2){
return zero(xmult(p,l1,l2))&&(l1.x-p.x)*(l2.x-p.x)<eps&&(l1.y-p.y)*(l2.y-p.y)<eps;
}

int intersect_in(point u1,point u2,point v1,point v2){
if (!dots_inline(u1,u2,v1)||!dots_inline(u1,u2,v2))
return !same_side(u1,u2,v1,v2)&&!same_side(v1,v2,u1,u2);
return
dot_online_in(u1,v1,v2)||dot_online_in(u2,v1,v2)||dot_online_in(v1,u1,u2)||dot_online_in(v2,u1,u2);
}


int intersect_in(line u,line v){
if (!dots_inline(u.a,u.b,v.a)||!dots_inline(u.a,u.b,v.b))
return !same_side(u.a,u.b,v)&&!same_side(v.a,v.b,u);
return dot_online_in(u.a,v)||dot_online_in(u.b,v)||dot_online_in(v.a,u)||dot_online_in(v.b,u);
}


struct qnode
{
	int v; typec c;
	qnode (int vv = 0, typec cc = 0) : v(vv), c(cc) {}
	bool operator < (const qnode& r) const { return c>r.c; }
};

void dijkstra(int n, const int src)
{
	qnode mv;
	int i, j, k, pre;
	priority_queue<qnode> que;
	vis[src] = 1; dist[src] = 0;
	que.push(qnode(src, 0));
	for (pre = src, i=1; i<n; i++)
	{
		for (j = head[pre]; j != -1; j = nxt[j])
		{
			k = pnt[j];
			if (vis[k] == 0 &&dist[pre] + cost[j] < dist[k])
			{
				dist[k] = dist[pre] + cost[j];
				que.push(qnode(pnt[j], dist[k]));
				prev[k] = pre;
			}
		}
		while (!que.empty() && vis[que.top().v] == 1)
		que.pop();
		if (que.empty()) break;
		mv = que.top(); que.pop();
		vis[pre = mv.v] = 1;
	}
}

inline void addedge(int u, int v, typec c)
{
	pnt[e] = v; cost[e] = c; nxt[e] = head[u]; head[u] = e++;
}
void init()
{
	int i;
	cnt=ncnt=e = 0;
	memset(head, -1, sizeof(head));
	memset(vis, 0, sizeof(vis));
	memset(prev, -1, sizeof(prev));
	for (i = 0; i < V; i++) dist[i] = inf;
}
inline void addline(line in)
{
	l[cnt++]=in;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("DOORS.IN","r",stdin);
 //   freopen("out.txt","w",stdout);
#endif
	line dir;
	dir.a.x=0;dir.a.y=5;dir.b.x=10;dir.b.y=5;
	while(scanf("%d",&n)==1 && n!=-1)
	{
		if(n==0)
		{
			printf("10.00\n");
			continue;
		}
		init();
		line tmp;
		for(int i=0;i<n;i++)
		{
            scanf("%lf",&tmp.a.x);
            tmp.b.x=tmp.a.x;

            double y;
            scanf("%lf",&y);

            tmp.a.y=0;tmp.b.y=y;
			ll[ncnt++]=tmp;
            if(intersect_in(dir,tmp))	addline(tmp);

            scanf("%lf",&y);
            tmp.a.y=y;
            scanf("%lf",&y);
            tmp.b.y=y;

			ll[ncnt++]=tmp;
            if(intersect_in(dir,tmp))	addline(tmp);

            scanf("%lf",&y);
            tmp.a.y=y;
            tmp.b.y=10;
			ll[ncnt++]=tmp;
            if(intersect_in(dir,tmp))	addline(tmp);
		}

		for(int i=0;i<cnt;i++)
		{
		    for(int j=0;j<2;j++)
		    {
		        point p1;
		        if(j==0)    p1=l[i].a;
		        else    p1=l[i].b;
		        bool flag=true;
		        for(int k=0;k<ncnt;k++)
		        {
		            if(l[i]!=ll[k] && intersect_in(dir.a,p1,ll[k].a,ll[k].b))
		            {
		                flag=false;
		                break;
		            }
		        }
		        if(flag)
                    addedge(0,2*i+j+1,distances(dir.a,p1));

                flag=true;
                for(int k=0;k<ncnt;k++)
		        {
		            if(l[i]!=ll[k] && intersect_in(dir.b,p1,ll[k].a,ll[k].b))
		            {
		                flag=false;
		                break;
		            }
		        }
		        if(flag)
                    addedge(2*i+j+1,2*cnt+1,distances(dir.b,p1));
		    }
		}

		for(int i=0;i<cnt;i++)
		{
		    for(int j=i+1;j<cnt;j++)
		    {
		        for(int a=0;a<2;a++)
		        {
		            for(int b=0;b<2;b++)
		            {
		                point p1,p2;
		                if(a==0)    p1=l[i].a;
		                else    p1=l[i].b;
		                if(b==0)    p2=l[j].a;
		                else    p2=l[j].b;

		                bool flag=true;
		                for(int k=0;k<ncnt;k++)
		                {
		                    if(l[i]!=ll[k] && l[j]!=ll[k] &&intersect_in(p1,p2,ll[k].a,ll[k].b))
		                    {
		                        flag=false;
		                        break;
		                    }
		                }
		                if(flag)
                            addedge(2*i+a+1,2*j+b+1,distances(p1,p2));
		            }
		        }
		    }
		}

		if(cnt!=0)
		{
            dijkstra(2*cnt+2,0);

            printf("%.2f\n",dist[2*cnt+1]);
		}
		else
		{
		    printf("%.2f\n",10.0);
		}

	}
	return 0;
}
