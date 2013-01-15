#include<cstdio>
#include<cstdlib>

#define eps 1e-8
#define zero(x) (((x)>0?(x):-(x))<eps)

const int MAXN=55;

struct point{double x,y;}p[MAXN],convex[MAXN];
int n;
//ŒÆËã cross product (P1-P0)x(P2-P0)
double xmult(point p1,point p2,point p0){
	return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
//graham Ëã·šË³Ê±Õë¹¹Ôì°üº¬ËùÓÐ¹²ÏßµãµÄÍ¹°ü,O(nlogn)
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
	qsort(p+1,n-1,sizeof(point),graham_cp);
	for (ch[0]=p[0],ch[1]=p[1],ch[2]=p[2],s=i=3;i<n;ch[s++]=p[i++])
		for (;s>2&&xmult(ch[s-2],p[i],ch[s-1])<-eps;s--);
}
//¹¹ÔìÍ¹°üœÓ¿Úº¯Êý,Ž«ÈëÔ­ÊŒµãŒ¯ŽóÐ¡ n,µãŒ¯ p(p Ô­ÓÐË³Ðò±»ŽòÂÒ!)
//·µ»ØÍ¹°üŽóÐ¡,Í¹°üµÄµãÔÚ convex ÖÐ
//²ÎÊý maxsize Îª 1 °üº¬¹²Ïßµã,Îª 0 ²»°üº¬¹²Ïßµã,È±Ê¡Îª 1
//²ÎÊý clockwise Îª 1 Ë³Ê±Õë¹¹Ôì,Îª 0 ÄæÊ±Õë¹¹Ôì,È±Ê¡Îª 1
//ÔÚÊäÈëœöÓÐÈôžÉ¹²ÏßµãÊ±Ëã·š²»ÎÈ¶š,¿ÉÄÜÓÐŽËÀàÇé¿öÇëÁíÐÐŽŠÀí!
//²»ÄÜÈ¥µôµãŒ¯ÖÐÖØºÏµÄµã
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

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	n=0;
	while(scanf("%lf %lf",&p[n].x,&p[n].y)==2)
		n++;
	
	int cnt=graham(n,p,convex,1,0);
	int pos;
	for(int i=0;i<cnt;i++)
	{
		if(p[i].x==0 && p[i].y==0)
		{
			pos=i;
			break;
		}
	}
	for(int j=0;j<cnt;j++)
	{
		printf("(%.f,%.f)\n",p[(pos-j+cnt)%cnt].x,p[(pos-j+cnt)%cnt].y);
	}
	return 0;
}
