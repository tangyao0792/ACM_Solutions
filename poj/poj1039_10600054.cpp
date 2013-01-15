#include<cstdio>
#include <math.h>
#define eps 1e-8
#define zero(x) (((x)>0?(x):-(x))<eps)
#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)

const long long INF=(1ll)<<50;
const int MAXN=102;

struct point{double x,y;
    bool operator ==(const point t) const
    {
        return x==t.x && y==t.y;
    }
}p[MAXN];
struct line{point a,b;}l[MAXN];

double xmult(point p1,point p2,point p0){
return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}

int opposite_side(point p1,point p2,line l){
return xmult(l.a,p1,l.b)*xmult(l.a,p2,l.b)<-eps;
}

point intersection(line u,line v){
point ret=u.a;
double t=((u.a.x-v.a.x)*(v.a.y-v.b.y)-(u.a.y-v.a.y)*(v.a.x-v.b.x))
/((u.a.x-u.b.x)*(v.a.y-v.b.y)-(u.a.y-u.b.y)*(v.a.x-v.b.x));
ret.x+=(u.b.x-u.a.x)*t;
ret.y+=(u.b.y-u.a.y)*t;
return ret;
}

int intersect_ex(line u,line v){
return opposite_side(u.a,u.b,v)&&opposite_side(v.a,v.b,u);
}
int parallel(line u,line v){
return zero((u.a.x-u.b.x)*(v.a.y-v.b.y)-(v.a.x-v.b.x)*(u.a.y-u.b.y));
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

int intersect_in(line u,line v){
if (!dots_inline(u.a,u.b,v.a)||!dots_inline(u.a,u.b,v.b))
return !same_side(u.a,u.b,v)&&!same_side(v.a,v.b,u);
return dot_online_in(u.a,v)||dot_online_in(u.b,v)||dot_online_in(v.a,u)||dot_online_in(v.b,u);
}



int n,cnt;
double left,right,ans;

void solve()
{
    ans=-INF;
    left--;
    right++;
    for(int i=0;i<cnt/2;i++)
        for(int j=cnt/2;j<cnt;j++)
        for(int ii=0;ii<2;ii++)
        for(int jj=0;jj<2;jj++)
        {
            point p1,p2,p3;
            if(ii==0)
                p1=l[i].a;
            else
                p1=l[i].b;
            if(jj==0)
                p2=l[j].a;
            else
                p2=l[j].b;
            if(p1.x==p2.x)continue;
            line tmp;
            tmp.a.x=left;tmp.b.x=right;
            double k=(p1.y-p2.y)/(p1.x-p2.x);
            tmp.a.y=k*(left-p2.x)+p2.y;
            tmp.b.y=k*(right-p2.x)+p2.y;

            if(!intersect_in(l[cnt],tmp))   continue;


            bool flag=true;
            int pos=cnt-1;
            for(int iii=0;iii<n;iii++)
            {
                line up;
                up.a=p[iii];
                up.b=p[iii+n];
                if(!intersect_in(tmp,up))
                {
                    pos=iii;
                    flag=false;
                    break;
                }
            }
            if( flag )
            {
                puts("Through all the pipe.");
                return;
            }
            double tmpans;
            if(intersect_in(l[pos-1],tmp)
               && intersect_in(l[pos-1+cnt/2],tmp))
            {
                p3=intersection(l[pos-1],tmp);
                tmpans=p3.x;
                p3=intersection(l[pos-1+cnt/2],tmp);
                tmpans=max(tmpans,p3.x);
            }
            else if(intersect_in(l[pos-1],tmp))
            {
                p3=intersection(l[pos-1],tmp);
                tmpans=p3.x;
            }
            else
            {
                p3=intersection(l[pos-1+cnt/2],tmp);
                tmpans=p3.x;
            }

                ans=max(ans,tmpans);
        }
        printf("%.2f\n",ans+eps);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while(scanf("%d",&n)==1 && n)
	{
		cnt=0;
		for(int i=0;i<n;i++)
		{
			scanf("%lf %lf",&p[i].x,&p[i].y);
			if(i==0 || left>eps+p[i].x)
			{
				left=p[i].x;
			}
			if(i==0 || right+eps<p[i].x)
			{
				right=p[i].x;
			}
			p[i+n]=p[i];
			p[i+n].y--;
		}

		for(int i=1;i<n;i++)
		{
			l[cnt].a=p[i-1];
			l[cnt++].b=p[i];
		}

		for(int i=n+1;i<2*n;i++)
		{
			l[cnt].a=p[i-1];
			l[cnt++].b=p[i];
		}
		l[cnt].a=p[0];
		l[cnt].b=p[n];
		l[cnt+1].a=p[n-1];
		l[cnt+1].b=p[2*n-1];
		solve();
	}
	return 0;
}
