#include<cstdio>
#include<iostream>
#include<cstring>

using namespace std;

const int MAXN=100010;

#define eps 1e-8
#define zero(x) (((x)>0?(x):-(x))<eps)

struct point{double x,y;};

struct line
{
	point a,b;
}l[MAXN];

int q[2][MAXN],q2[MAXN];
int f[2],r[2];
int n;


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
#endif
	while(scanf("%d",&n)==1 && n)
	{
	    f[0]=f[1]=r[0]=r[1]=0;
		for(int i=0;i<n;i++)
		{
		    scanf("%lf %lf %lf %lf",&l[i].a.x,&l[i].a.y,&l[i].b.x,&l[i].b.y);
            int get=i%2;
            int set=(i+1)%2;
            f[set]=r[set]=0;
            while(f[get]!=r[get])
            {
                int top=q[get][r[get]++];
                if(!intersect_in(l[top],l[i]))
                {
                    q[set][f[set]++]=top;
                }
            }
            q[set][f[set]++]=i;
		}

		printf("Top sticks: ");
        int get=(n)%2;
        int top=q[get][r[get]++];
        printf("%d",top+1);

        while(f[get]!=r[get])
        {
            int top=q[get][r[get]++];
            printf(", %d",top+1);
        }
        printf(".\n");
	}

	return 0;
}
