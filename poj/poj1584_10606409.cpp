#include<cstdio>
#include <math.h>
#define eps 1e-8
#define zero(x) (((x)>0?(x):-(x))<eps)

const int MAXN=1111;

struct point
{
	double x,y;
	bool operator == (const point &t)	const
	{
		return t.x==x && t.y==y;
	}
    point operator +(const point t)const
    {
        point ans;
        ans.x=x+t.x;
        ans.y=y+t.y;
        return ans;
    }
    point operator -(const point t)const
    {
        point ans;
        ans.x=x-t.x;
        ans.y=y-t.y;
        return ans;
    }
}p[MAXN];
struct line{point a,b;}l[MAXN];

double xmult(point p1,point p2,point p0){
return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}

double distances(point p1,point p2){
return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
int same_side(point p1,point p2,point l1,point l2){
return xmult(l1,p1,l2)*xmult(l1,p2,l2)>eps;
}
int opposite_side(point p1,point p2,point l1,point l2){
return xmult(l1,p1,l2)*xmult(l1,p2,l2)<-eps;
}
double disptoline(point p,line l){
return fabs(xmult(p,l.a,l.b))/distances(l.a,l.b);
}

int n;
double radius,px,py;

int solve()
{
	bool flag=true;
	for(int i=0;i<n && flag;i++)
	{
		point p1,p2,p3,p4;
		p1=l[i].a;p2=l[i].b;
		for(int j=0;j<n && flag;j++)
		{
			p3=p[j];
			if(p3==p1 || p3==p2)	continue;
			for(int k=j+1;k<n;k++)
			{
				p4=p[k];
				if(p4==p1 || p4==p2 || p4==p3)
					continue;

				if(opposite_side(p3,p4,p1,p2))
				{
					flag=false;
					break;
				}
			}
		}
	}
	if(!flag)	return 1;
	point peg;
	peg.x=px;peg.y=py;

	double direct=xmult(l[0].a-peg,l[0].b-l[0].a,peg-peg);
	for(int i=1;i<n;i++)
	{
	    if(xmult(l[i].a-peg,l[i].b-l[i].a,peg-peg)*direct<-eps)
            return 2;
	}

	for(int i=0;i<n;i++)
	{
		double tmp=disptoline(peg,l[i]);
		if(tmp+eps<radius)
			return 2;
	}
	return 0;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("pD1.in","r",stdin);
	freopen("out.txt","w",stdout);
#endif
	while(scanf("%d",&n)==1 && n>=3)
	{
		scanf("%lf %lf %lf",&radius,&px,&py);
		for(int i=0;i<n;i++)
			scanf("%lf %lf",&p[i].x,&p[i].y);
		for(int i=0;i<n;i++)
		{
			l[i].a=p[i];
			l[i].b=p[(i+1+n)%n];
		}
		int ans=solve();
		if(ans==1)
			puts("HOLE IS ILL-FORMED");
		else if(ans==2)
			puts("PEG WILL NOT FIT");
		else
			puts("PEG WILL FIT");
	}
	return 0;
}
