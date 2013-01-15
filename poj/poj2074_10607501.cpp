#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>

using namespace std;

#define eps 1e-8
#define zero(x) (((x)>0?(x):-(x))<eps)
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

const int MAXN=1111;
const long long INF=(1ll)<<30;

struct point{double x,y;};
struct line{point a,b;}l[MAXN],shadow[MAXN],pl,house;

double xmult(point p1,point p2,point p0){
return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
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
point intersection(line u,line v){
point ret=u.a;
double t=((u.a.x-v.a.x)*(v.a.y-v.b.y)-(u.a.y-v.a.y)*(v.a.x-v.b.x))
/((u.a.x-u.b.x)*(v.a.y-v.b.y)-(u.a.y-u.b.y)*(v.a.x-v.b.x));
ret.x+=(u.b.x-u.a.x)*t;
ret.y+=(u.b.y-u.a.y)*t;
return ret;
}

int n;

void swap(double &a,double &b)
{
	if(a>b)
	{
		double tmp=a;
		a=b;
		b=tmp;
	}
}

line getline(point p1,point p2)
{
	line tmp;
	if(p1.x==p2.x)
	{
		tmp.a.x=tmp.b.x=p1.x;
		tmp.a.y=-INF;
		tmp.b.y=INF;
		return tmp;
	}
	double k=(p1.y-p2.y)/(p1.x-p2.x);
	tmp.a.x=-INF;
	tmp.a.y=k*(-INF-p1.x)+p1.y;
	tmp.b.x=INF;
	tmp.b.y=k*(INF-p1.x)+p1.y;

	return tmp;
}
bool comp(line a,line b)
{
	return a.a.x+eps<b.a.x;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
   // freopen("out.txt","w",stdout);
#endif
	double x1,x2,y;
	while(scanf("%lf %lf %lf",&x1,&x2,&y)==3)
	{
		if(x1==0 && x2==0 && y==0)break;
		swap(x1,x2);
		house.a.x=x1;house.b.x=x2;
		house.a.y=house.b.y=y;

		scanf("%lf %lf %lf",&x1,&x2,&y);
		swap(x1,x2);
		pl.a.x=x1;pl.b.x=x2;pl.a.y=pl.b.y=y;

		scanf("%d",&n);

		for(int i=0;i<n;i++)
		{
			scanf("%lf %lf %lf",&x1,&x2,&y);
			swap(x1,x2);
			if(y>house.a.y+eps || y+eps<pl.a.y || y==house.a.y || y==pl.a.y)
			{
				i--;
				n--;
				continue;
			}
			l[i].a.x=x1;l[i].b.x=x2;
			l[i].a.y=l[i].b.y=y;
		}
        line pll=getline(pl.a,pl.b);
		for(int i=0;i<n;i++)
		{
			line tmp=getline(house.a,l[i].b);
			point ip;

            ip=intersection(tmp,pll);
            shadow[i].b=ip;

			tmp=getline(house.b,l[i].a);

            ip=intersection(tmp,pll);
            shadow[i].a=ip;

			if((shadow[i].a.x+eps<pl.a.x && shadow[i].b.x+eps<pl.a.x) ||
      (shadow[i].a.x>pl.b.x+eps && shadow[i].b.x>pl.b.x+eps))
			{
			    i--;
			    n--;
			    continue;
			}
			shadow[i].a.x=max(shadow[i].a.x,pl.a.x);
			shadow[i].b.x=min(shadow[i].b.x,pl.b.x);
		}

        if(n==0)
        {
            printf("%.2f\n",pl.b.x-pl.a.x+eps);
            continue;
        }

		sort(shadow,shadow+n,comp);
		double ans=-1;
		ans=max(ans,shadow[0].a.x-pl.a.x);
		ans=max(ans,pl.b.x-shadow[n-1].b.x);
		double maxright=pl.a.x;
		for(int i=0;i<n-1;i++)
		{
		    maxright=max(maxright,shadow[i].b.x);
			double r=shadow[i+1].a.x;
            ans=max(ans,r-maxright);
		}
		if(ans<eps)
			puts("No View");
		else
			printf("%.2f\n",ans+eps);
	}
	return 0;
}
