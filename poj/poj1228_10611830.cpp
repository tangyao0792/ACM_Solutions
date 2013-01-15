#include<cstdio>
#include<cmath>
#include<cstdlib>

using namespace std;

#define eps 1e-8
#define zero(x) (((x)>0?(x):-(x))<eps)


const int MAXN=1111;

struct point{double x,y;}p[MAXN],convex[MAXN];
// ¼ÆËã cross product (P1-P0)x(P2-P0)
double xmult(point p1,point p2,point p0){
		return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);

}

double distances(point p1,point p2){
		return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
point p1,p2;
int graham_cp(const void* a,const void* b){
		double ret=xmult(*((point*)a),*((point*)b),p1);
		return zero(ret)?(xmult(*((point*)a),*((point*)b),p2)>0?1:-1):(ret>0?1:-1);
}
void _graham(int n,point* p,int& s,point* ch){
		int i,k=0;
		for (p1=p2=p[0],i=1;i<n;p2.x+=p[i].x,p2.y+=p[i].y,i++)
				if (p1.y-p[i].y>eps||(zero(p1.y-p[i].y)&&p1.x>p[i].x))
						p1=p[k=i];
		p2.x/=n,p2.y/=n;
		p[k]=p[0],p[0]=p1;
		qsort(p+1,n-1,sizeof (point),graham_cp);
		for (ch[0]=p[0],ch[1]=p[1],ch[2]=p[2],s=i=3;i<n;ch[s++]=p[i++])
				for (;s>2&&xmult(ch[s-2],p[i],ch[s-1])<-eps;s--);
}
int graham(int n,point* p,point* convex,int maxsize=1,int dir=1){
		point* temp=new point[n];
		int s,i;
		_graham(n,p,s,temp);
		for (convex[0]=temp[0],n=1,i=(dir?1:(s-1));dir?(i<s):i;i+=(dir?1:-1))
				if (maxsize||!zero(xmult(temp[i-1],temp[i],temp[(i+1)%s])))
						convex[n++]=temp[i];
		delete []temp;
		return n;
}

point p0;
bool comp(point p1,point p2)
{
	double tmp=xmult(p1,p2,p0);
	if(tmp<-eps)
		return true;
	if(tmp>eps)
		return false;
	return distances(p1,p0) < distances(p2,p0);
}
int n;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	p0.x=0;p0.y=0;
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i=0;i<n;i++)
		{
			scanf("%lf %lf",&p[i].x,&p[i].y);
		}
		bool flag=true;
		int cnt=0;
		int no=0;
		if(n<3)
		{
		    flag=false;
		    goto answer;
		}

		n=graham(n,p,convex);
		while(cnt<n)
		{
			point p1=convex[cnt%n],p2=convex[(cnt+1)%n];
			cnt+=2;

			int c=2;
			while(abs(xmult(p1,p2,convex[cnt%n]))<eps)
			{
				c++;
				cnt++;
				if(cnt>=n)
                    goto answer;
			}
			if(c<3)
			{
				flag=false;
				break;
			}
			no++;
			cnt--;
		}
    answer:
        if(no<2)flag=false;
		if(flag)
			puts("YES");
		else
			puts("NO");
	}
	return 0;
}
