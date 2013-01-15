#include<cstdio>
#include <math.h>

#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

#define eps 1e-8
#define zero(x) (((x)>0?(x):-(x))<eps)

struct point{double x,y;};
struct line{point a,b;};

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


int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	freopen("out","w",stdout);
#endif

	int t;
	scanf("%d",&t);
	line l,tmp;
	double x[2],y[2];
	while(t--)
	{
		scanf("%lf %lf %lf %lf %lf %lf %lf %lf",&l.a.x,&l.a.y,&l.b.x,&l.b.y,&x[0],&y[0],&x[1],&y[1]);
		bool flag = true;
		for(int i=0;i<2 && flag;i++)
		{
            tmp.a.x=x[i];tmp.b.x=x[i];
			tmp.a.y=y[0];tmp.b.y=y[1];
            if(intersect_in(l,tmp))
            {
                flag=false;
                break;
            }
		}
        for(int i=0;i<2 && flag;i++)
		{
            tmp.a.y=y[i];tmp.b.y=y[i];
			tmp.a.x=x[0];tmp.b.x=x[1];
            if(intersect_in(l,tmp))
            {
                flag=false;
                break;
            }
		}
		if((max(l.a.x,l.b.x)<=max(x[0],x[1]) &&
     min(l.a.x,l.b.x)>=min(x[0],x[1]))&&(max(l.a.y,l.b.y)<=max(y[0],y[1]) &&
     min(l.a.y,l.b.y)>=min(y[0],y[1])))
        flag = false;

		if(!flag)
			puts("T");
		else
			puts("F");
	}

	return 0;
}
