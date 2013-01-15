#include<cstdio>

#define eps 1e-8
#define zero(x) (((x)>0?(x):-(x))<eps)
struct point{double x,y;};
struct line{point a,b;};

int parallel(point u1,point u2,point v1,point v2)
{
	return zero((u1.x-u2.x)*(v1.y-v2.y)-(v1.x-v2.x)*(u1.y-u2.y));
}

point intersection(line u,line v)
{
	point ret=u.a;
	double t=((u.a.x-v.a.x)*(v.a.y-v.b.y)-(u.a.y-v.a.y)*(v.a.x-v.b.x))/((u.a.x-u.b.x)*(v.a.y-v.b.y)-(u.a.y-u.b.y)*(v.a.x-v.b.x));
	ret.x+=(u.b.x-u.a.x)*t;
	ret.y+=(u.b.y-u.a.y)*t;
	return ret;
}


int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	int t;
	scanf("%d",&t);
	puts("INTERSECTING LINES OUTPUT");
	line l1,l2;
	while(t--)
	{
		scanf("%lf %lf %lf %lf",&l1.a.x,&l1.a.y,&l1.b.x,&l1.b.y);	
		scanf("%lf %lf %lf %lf",&l2.a.x,&l2.a.y,&l2.b.x,&l2.b.y);	
		if(parallel(l1.a,l1.b,l2.a,l2.b))
		{
			if(parallel(l1.a,l1.b,l1.b,l2.a))
			{
				puts("LINE");
			}
			else
			{
				puts("NONE");
			}
		}
		else
		{
			point ans=intersection(l1,l2);
			printf("POINT %.2f %.2f\n",ans.x,ans.y);
		}
	}
	puts("END OF OUTPUT");
	return 0;
}
