#include<cstdio>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

const int MAXN=35;
const int MAXP=2222;
const int MAXE=11111;

int vis[MAXP];
int first[MAXP];
int u[MAXE],v[MAXE],next[MAXE];
int cnte;
int n;

#define eps 1e-8
#define zero(x) (((x)>0?(x):-(x))<eps)
struct point
{
	double x,y;
}p[555],ip[55],start;
int cnt,icnt;

struct line
{
	point a,b;
}l[MAXN];

double xmult(point p1,point p2,point p0){
return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}

int parallel(line u,line v)
{
	return zero((u.a.x-u.b.x)*(v.a.y-v.b.y)-(v.a.x-v.b.x)*(u.a.y-u.b.y));
}

point intersection(line u,line v)
{
	point ret=u.a;
	double t=((u.a.x-v.a.x)*(v.a.y-v.b.y)-(u.a.y-v.a.y)*(v.a.x-v.b.x))/((u.a.x-u.b.x)*(v.a.y-v.b.y)-(u.a.y-u.b.y)*(v.a.x-v.b.x));
	ret.x+=(u.b.x-u.a.x)*t;
	ret.y+=(u.b.y-u.a.y)*t;
	return ret;
}


int dots_inline(point p1,point p2,point p3){
return zero(xmult(p1,p2,p3));
}

int dot_online_in(point p,line l){
return zero(xmult(p,l.a,l.b))&&(l.a.x-p.x)*(l.b.x-p.x)<eps&&(l.a.y-p.y)*(l.b.y-p.y)<eps;
}

int same_side(point p1,point p2,line l){
return xmult(l.a,p1,l.b)*xmult(l.a,p2,l.b)>eps;
}

int intersect_in(line u,line v){
if (!dots_inline(u.a,u.b,v.a)||!dots_inline(u.a,u.b,v.b))
return !same_side(u.a,u.b,v)&&!same_side(v.a,v.b,u);
return dot_online_in(u.a,v)||dot_online_in(u.b,v)||dot_online_in(v.a,u)||dot_online_in(v.b,u);
}

int opposite_side(point p1,point p2,line l){
return xmult(l.a,p1,l.b)*xmult(l.a,p2,l.b)<-eps;
}

int intersect_ex(line u,line v){
return opposite_side(u.a,u.b,v)&&opposite_side(v.a,v.b,u);
}

inline bool isEdge(int num)
{
	return (zero(p[num].x) || zero(p[num].x-100.0)|| (zero(p[num].y) || zero(p[num].y-100.0)));
}

bool comp(point a,point b)
{
    if(a.x==b.x)
        return a.y<b.y;
	return a.x<b.x;
}

inline void addedge(int x,int y)
{
	u[cnte]=x;v[cnte]=y;
	next[cnte]=first[x];
	first[x]=cnte++;
}

struct NODE
{
	int no,dist;
};

int bfs()
{
	queue<NODE> q;
	NODE tmp;
	tmp.no=cnt-1;tmp.dist=0;
	q.push(tmp);
	while(!q.empty())
	{
		tmp=q.front();
		q.pop();
		if(vis[tmp.no])continue;
		vis[tmp.no]=1;
		for(int e=first[tmp.no];e!=-1;e=next[e])
		{
			NODE nt;
			nt.no=v[e];
			nt.dist=tmp.dist+1;
			if(isEdge(nt.no))
				return nt.dist;
			q.push(nt);
		}
	}
	return -1;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("./D/D.28.dat","r",stdin);
#endif

	scanf("%d",&n);
	cnte=cnt=0;
	memset(vis,0,sizeof(vis));
	memset(first,-1,sizeof(first));

	l[n].a.x=0;l[n].a.y=0;l[n].b.x=0;l[n].b.y=100;
	l[n+1].a.x=0;l[n+1].a.y=0;l[n+1].b.x=100;l[n+1].b.y=0;
	l[n+2].a=l[n].b;l[n+2].b.x=100;l[n+2].b.y=100;
	l[n+3].a=l[n+2].b;l[n+3].b=l[n+1].b;

	for(int i=0;i<n;i++)
	{
		scanf("%lf %lf %lf %lf",&l[i].a.x,&l[i].a.y,&l[i].b.x,&l[i].b.y);
	}
	n=n+4;


	for(int i=0;i<n;i++)
	{
		icnt=0;
		for(int j=0;j<n;j++)
		{
			if(i!=j)
			{
				if(parallel(l[i],l[j])||(!intersect_in(l[i],l[j])))	continue;
				ip[icnt++]=intersection(l[i],l[j]);
			}
		}
		sort(ip,ip+icnt,comp);
		for(int j=1;j<icnt;j++)
		{
			point mid;
			mid.x=(ip[j-1].x+ip[j].x)/2;
			mid.y=(ip[j-1].y+ip[j].y)/2;
			p[cnt++]=mid;
		}
	}
	scanf("%lf %lf",&start.x,&start.y);
	p[cnt++]=start;
	for(int i=0;i<cnt;i++)
	{
		for(int j=0;j<cnt;j++)
		{
			if(i!=j)
			{
				bool flag=true;
				line tmp;
				tmp.a=p[i];tmp.b=p[j];
				for(int k=0;k<n;k++)
				{
					if(intersect_ex(tmp,l[k]))
					{
						flag=false;
						break;
					}
				}
				if(flag)
				{
					addedge(i,j);
					addedge(j,i);
				}
			}
		}
	}
	printf("Number of doors = %d\n",bfs());
	return 0;
}
