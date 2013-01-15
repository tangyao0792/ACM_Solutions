#include<cstdio>

#include <math.h>
#define eps 1e-8
#define zero(x) (((x)>0?(x):-(x))<eps)
#define abs(x) ((x)<eps?(-x):(x))
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

struct point{double x,y;};
struct line{point a,b;};

line l1,l2;

double xmult(point p1,point p2,point p0){
return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
int dots_inline(point p1,point p2,point p3){
return zero(xmult(p1,p2,p3));
}
int dot_online_in(point p,line l){
return zero(xmult(p,l.a,l.b))&&(l.a.x-p.x)*(l.b.x-p.x)<eps&&(l.a.y-p.y)*(l.b.y-p.y)<eps;
}
int dot_online_ex(point p,line l){
return dot_online_in(p,l)&&(!zero(p.x-l.a.x)||!zero(p.y-l.a.y))&&(!zero(p.x-l.b.x)||!zero(p.y-
l.b.y));
}
int same_side(point p1,point p2,line l){
return xmult(l.a,p1,l.b)*xmult(l.a,p2,l.b)>eps;
}
int opposite_side(point p1,point p2,line l){
return xmult(l.a,p1,l.b)*xmult(l.a,p2,l.b)<-eps;
}
int intersect_in(line u,line v){
if (!dots_inline(u.a,u.b,v.a)||!dots_inline(u.a,u.b,v.b))
return !same_side(u.a,u.b,v)&&!same_side(v.a,v.b,u);
return dot_online_in(u.a,v)||dot_online_in(u.b,v)||dot_online_in(v.a,u)||dot_online_in(v.b,u);
}
int intersect_ex(line u,line v){
return opposite_side(u.a,u.b,v)&&opposite_side(v.a,v.b,u);
}
point intersection(line u,line v){
point ret=u.a;
double t=((u.a.x-v.a.x)*(v.a.y-v.b.y)-(u.a.y-v.a.y)*(v.a.x-v.b.x))/((u.a.x-u.b.x)*(v.a.y-v.b.y)-(u.a.y-u.b.y)*(v.a.x-v.b.x));
ret.x+=(u.b.x-u.a.x)*t;
ret.y+=(u.b.y-u.a.y)*t;
return ret;
}

void swap(point &p1,point &p2)
{
	point tmp=p1;
	p1=p2;
	p2=tmp;
}
int parallel(line u,line v){
return zero((u.a.x-u.b.x)*(v.a.y-v.b.y)-(v.a.x-v.b.x)*(u.a.y-u.b.y));
}

double solve()
{
	if(l1.a.y==l1.b.y || l2.a.y==l2.b.y || (!intersect_in(l1,l2)) ||
    parallel(l1,l2))
		return 0;

	if(l1.a.y>l1.b.y+eps)	swap(l1.a,l1.b);
	if(l2.a.y>l2.b.y+eps)	swap(l2.a,l2.b);

	point ip=intersection(l1,l2);

	if(l1.b.y<ip.y || l2.b.y+eps<ip.y)
		return 0;

	point h,l;
	bool flag=true;
	if(l1.b.y>l2.b.y+eps)
	{
		h=l1.b;
		l=l2.b;
	}
	else if(l1.b.y<l2.b.y-eps)
	{
		h=l2.b;
		l=l1.b;
	}
	else
	{
	    flag=false;
	    h=l2.b;
		l=l1.b;
	}

	if(flag && ((h.x>=l.x && ip.x+eps< l.x &&(l.y-ip.y)*(h.x-ip.x) < (l.x-ip.x)*(h.y-ip.y)+eps) ||
             (h.x<=l.x && ip.x> l.x+eps&&(l.y-ip.y)*(h.x-ip.x) > (l.x-ip.x)*(h.y-ip.y)-eps)))
		return 0;

	line tmp;
	tmp.a.x=min(min(l1.a.x,l2.a.x),min(l1.b.x,l2.b.x));
	tmp.b.x=max(max(l1.a.x,l2.a.x),max(l1.b.x,l2.b.x));
	tmp.a.y=tmp.b.y=l.y;

	point p1=intersection(tmp,l1);
	point p2=intersection(tmp,l2);

	double dist=p1.x-p2.x;
	if(dist<-eps) dist*=-1;
	return dist*(l.y-ip.y)/2;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("data.txt","r",stdin);
	freopen("out.txt","w",stdout);
#endif

	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%lf %lf %lf %lf",&l1.a.x,&l1.a.y,&l1.b.x,&l1.b.y);
		scanf("%lf %lf %lf %lf",&l2.a.x,&l2.a.y,&l2.b.x,&l2.b.y);

		printf("%.2f\n",solve()+eps);

	}

	return 0;
}
