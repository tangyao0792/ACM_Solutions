/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include <math.h>


#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

const long long INF=(1ll)<<60;
#define eps 1e-12
#define zero(x) (((x)>0?(x):-(x))<eps)

int n;
struct point
{
    double x,y;
    bool operator == (point t) const
    {
        return t.x==x && t.y==y;
    }
}p[111];
struct line{point a,b;}l[111];

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
int parallel(line u,line v){
return zero((u.a.x-u.b.x)*(v.a.y-v.b.y)-(v.a.x-v.b.x)*(u.a.y-u.b.y));
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

typedef long long LL;

LL y[111],a[111],b[111];

int main(int argc, const char *argv[])
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int sn;
        scanf("%d %d",&sn,&n);
        double maxy=-INF,miny=INF,maxx=-INF,minx=INF;
        for(int i=0;i<n;i++)
        {
            scanf("%lf %lf",&p[i].x,&p[i].y);
            maxy=max(maxy,p[i].y);
            miny=min(miny,p[i].y);
            maxx=max(maxx,p[i].x);
            minx=min(minx,p[i].x);
        }
        for(int i=0;i<n;i++)
        {
            l[i].a=p[i];
            l[i].b=p[(i+1)%n];
        }

        line tmp;
        tmp.a.x=minx-100;
        tmp.b.x=maxx+100;
        int cnt=0;
        point p[4];
        for(LL i=LL(maxy)+1;i>=LL(miny)-1;i--)
        {
            tmp.a.y=tmp.b.y=i;
            int c=0;
            for(int j=0;j<n;j++)
            {

                if(!parallel(tmp,l[j]) && intersect_in(tmp,l[j]))
                {
                    p[c++]=intersection(tmp,l[j]);
                }
                if(c==0)    continue;
                for(int k=0;k<c-1;k++)
                    if(p[k]==p[c-1])
                    {
                        c--;
                        break;
                    }
                for(int k=0;k<n;k++)
                {
                    if(parallel(tmp,l[k]) && dot_online_in(p[c-1],l[k]))
                    {
                        c--;
                        break;
                    }
                }
                if(c==4)    break;
            }
            double left=INF,right=-INF;
            for(int j=0;j<c;j++)
            {
                left=min(left,p[j].x);
                right=max(right,p[j].x);
            }
//            left+=eps;
//            right+=eps;
            y[cnt]=i;
            if(zero(right-left) || c==0||c==1)    continue;

            if(zero(left-LL(left)))
            {
                a[cnt]=LL(left)+1;
            }
            else
            {
                if(left<-eps)
                    a[cnt]=LL(left);
                else if(left>eps)
                    a[cnt]=LL(left)+1;
                else
                    a[cnt]=0;
            }
            if(zero(right-LL(right)))
            {
                b[cnt]=LL(right)-1;
            }
            else
            {
                if(right<-eps)
                    b[cnt]=LL(right)-1;
                else if(right>eps)
                    b[cnt]=LL(right);
                else
                    b[cnt]=0;

            }
            if(a[cnt]>b[cnt])  continue;
            cnt++;
        }
        printf("%d %d\n",sn,cnt);
        for(int i=0;i<cnt;i++)
        {
            printf("%I64d %I64d %I64d\n",y[i],a[i],b[i]);
        }
    }
    return 0;
}
