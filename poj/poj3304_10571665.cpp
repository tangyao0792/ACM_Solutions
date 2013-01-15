#include<cstdio>
#include<cmath>

const double eps=1e-8;
const int MAXN=111;

#define zero(x) (((x)>0?(x):-(x))<eps)

struct point{double x,y;};

struct line{point a,b;}lines[MAXN];

int n;

double distance(point p1,point p2){
return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

double xmult(point p1,point p2,point p0){
return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}

int dots_inline(point p1,point p2,point p3){
return zero(xmult(p1,p2,p3));
}

int dot_online_in(point p,point l1,point l2){
return zero(xmult(p,l1,l2))&&(l1.x-p.x)*(l2.x-p.x)<eps&&(l1.y-p.y)*(l2.y-p.y)<eps;
}


int same_side(point p1,point p2,point l1,point l2){
return xmult(l1,p1,l2)*xmult(l1,p2,l2)>eps;
}


int intersect_in(point u1,point u2,point v1,point v2)
{
//	if (!dots_inline(u1,u2,v1)||!dots_inline(u1,u2,v2))
		return !same_side(u1,u2,v1,v2);
	return dot_online_in(u1,v1,v2)||dot_online_in(u2,v1,v2)||dot_online_in(v1,u1,u2)||dot_online_in(v2,u1,u2);
}
int opposite_side(point p1,point p2,line l)
{
    return xmult(l.a,p1,l.b)*xmult(l.a,p2,l.b)<-eps;
}
int opposite_side(point p1,point p2,point l1,point l2)
{
    return xmult(l1,p1,l2)*xmult(l1,p2,l2)<-eps;
}


int intersect_ex(line u,line v)
{
    return opposite_side(u.a,u.b,v)&&opposite_side(v.a,v.b,u);
}
int intersect_ex(point u1,point u2,point v1,point v2)
{
    return opposite_side(u1,u2,v1,v2)&&opposite_side(v1,v2,u1,u2);
}



int solve()
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			for(int a=0;a<2;a++)
			{
				for(int b=0;b<2;b++)
				{
					point p1,p2;
					if(a==0)p1=lines[i].a;
					else p1=lines[i].b;

					if(b==0)p2=lines[j].a;
					else p2=lines[j].b;

					double dis=distance(p1,p2);
					if(dis<1e-8)continue;

					bool flag=true;
					for(int k=0;k<n;k++)
					{
                            if(!intersect_in(lines[k].a,lines[k].b,p1,p2))
//					if(same_side(lines[k].a,lines[k].b,p1,p2))
//                        if(!intersect_ex(lines[k].a,lines[k].b,p1,p2))
						{
							flag=false;
							break;
						}
					}
					if(flag)
						return true;
				}
			}
		}
	}
	return false;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);

		for(int i=0;i<n;i++)
			scanf("%lf %lf %lf %lf",&lines[i].a.x,&lines[i].a.y,&lines[i].b.x,&lines[i].b.y);
		if(n==1 || n==2 ||solve())
			puts("Yes!");
		else
			puts("No!");
	}
	return 0;
}
