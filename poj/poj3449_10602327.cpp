#include<cstdio>
#include<cstring>
#include <math.h>
#include<iostream>
#include<algorithm>

using namespace std;

#define eps 1e-8
#define zero(x) (((x)>0?(x):-(x))<eps)

const int MAXN=30;
const int MAXL=25;
const char *l4="square";
const char *l1="line";
const char *l3="triangle";
const char *ln="polygon";
const char *rec="rectangle";
const double pi=3.1415926;

int n;

struct point
{
    double x,y;
    bool operator == (const point t)const
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
}pt[MAXL];
struct line{point a,b;};
struct polygon
{
	char name;
	int cnt;
	line l[MAXL];
}p[MAXN];

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
point rotate(point v,point p,double angle,double scale){
point ret=p;
v.x-=p.x,v.y-=p.y;
p.x=scale*cos(angle);
p.y=scale*sin(angle);
ret.x+=v.x*p.x-v.y*p.y;
ret.y+=v.x*p.y+v.y*p.x;
return ret;
}


bool comp(polygon a,polygon b)
{
	return a.name<b.name;
}

void input(char c)
{
	p[n].name=c;
	char shape[20];
	int x;
	cin>>shape;
	if(strcmp(shape,l1)==0)
		p[n].cnt=1;
	else if(strcmp(shape,l3)==0)
		p[n].cnt=3;
	else if(strcmp(shape,l4)==0 || strcmp(shape,rec)==0)
		p[n].cnt=4;
	else if(strcmp(shape,ln)==0)
	{
		scanf("%d",&x);
		p[n].cnt=x;
	}
	if(strcmp(shape,l4)==0)
	{
        cin>>c>>pt[0].x>>c>>pt[0].y>>c;
        cin>>c>>pt[2].x>>c>>pt[2].y>>c;

        pt[4].x=(pt[0].x+pt[2].x)/2;
        pt[4].y=(pt[0].y+pt[2].y)/2;

        pt[1]=rotate(pt[0],pt[4],pi/2,1);
        pt[3]=rotate(pt[0],pt[4],-pi/2,1);

        for(int i=0;i<p[n].cnt;i++)
        {
            p[n].l[i].a=pt[i];
            p[n].l[i].b=pt[(i+4+1)%4];
        }
	}
	else if(strcmp(shape,rec)==0)
	{
        for(int i=0;i<3;i++)
        {
            cin>>c>>pt[i].x>>c>>pt[i].y>>c;
        }
        pt[3]=pt[0]-pt[1];
        pt[3]=pt[3]+pt[2];

        for(int i=0;i<p[n].cnt;i++)
        {
            p[n].l[i].a=pt[i];
            p[n].l[i].b=pt[(i+4+1)%4];
        }
	}
	else
	{
	    int size;
	    if(p[n].cnt==1)  size=2;
	    else size=p[n].cnt;
        for(int i=0;i<size;i++)
        {
            cin>>c>>pt[i].x>>c>>pt[i].y>>c;
        }
        for(int i=0;i<p[n].cnt;i++)
        {
            p[n].l[i].a=pt[i];
            p[n].l[i].b=pt[(i+size+1)%size];
        }
	}

	n++;
}

int ans[MAXN];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	char c;
	while(cin>>c)
	{
		if(c=='.')	break;
		n=0;
		input(c);
		while(cin>>c)
		{
			if(c=='-')break;
			input(c);
		}
		sort(p,p+n,comp);
		int cnt=0;
		for(int i=0;i<n;i++)
		{
			memset(ans,0,sizeof(ans));
			for(int j=0;j<n;j++)
			{
			    if(i==j)    continue;
				bool flag=true;
				for(int a=0;a<p[i].cnt;a++)
					for(int b=0;b<p[j].cnt;b++)
						if(intersect_in(p[i].l[a],p[j].l[b]))
						{
							flag=false;
							break;
						}

				if(flag)
				{
					ans[j]=1;
				}
			}
			ans[i]=1;
			for(int j=0;j<n;j++)
                if(!ans[j])
                    cnt++;
			printf("%c ",p[i].name);
			if(cnt==0)
			{
				puts("has no intersections");
			}
			else if(cnt==1)
			{
				printf("intersects with");
				for(int j=0;j<n;j++)
				{
					if(ans[j]==0)
					{
						printf(" %c",p[j].name);
						cnt--;
						break;
					}
				}
				puts("");
			}
			else if(cnt==2)
			{
				printf("intersects with");
				for(int j=0;j<n;j++)
				{
					if(ans[j]==0)
					{
						cnt--;
						if(!cnt)
							printf(" and %c",p[j].name);
						else
							printf(" %c",p[j].name);
					}
				}
				puts("");
			}
			else
			{
				printf("intersects with");
				for(int j=0;j<n;j++)
				{
					if(ans[j]==0)
					{
						cnt--;
						if(!cnt)
							printf(" and %c",p[j].name);
						else
							printf(" %c,",p[j].name);
					}
				}
				puts("");
			}
		}
		puts("");
	}

	return 0;
}
