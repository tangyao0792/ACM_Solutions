#include<cstdio>
#include <math.h>
#include<cstring>
#define eps 1e-8
#define zero(x) (((x)>0?(x):-(x))<eps)

const int MAXN=55;

struct point{double x,y;}p[MAXN];
struct line{point a,b;};

double xmult(point p1,point p2,point p0){
return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}

double distances(point p1,point p2){
return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}



int n;
int number[MAXN];
int vis[MAXN];

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
		int pos=0;
		for(int i=0;i<n;i++)
		{
			scanf("%d %lf %lf",&number[i],&p[i].x,&p[i].y);
			if(p[pos].y>p[i].y)	pos=i;
		}

		printf("%d %d",n,number[pos]);
		memset(vis,0,sizeof(vis));
		vis[pos]=1;

		point last=p[pos];

		for(int i=1;i<n;i++)
		{
			double dist;

			for(int j=0;j<n;j++)
				if(!vis[j])
				{
					pos=j;
					break;
				}
			for(int j=pos+1;j<n;j++)
			{
				if(vis[j])continue;


				double tmp=xmult(p[pos],p[j],last);
				double tmpdist=distances(last,p[j]);
				if(tmp<-eps || (zero(tmp) && tmpdist<dist))
				{
					pos=j;
					dist=tmpdist;
				}
			}
			printf(" %d",number[pos]);
			vis[pos]=1;
			last=p[pos];
		}
        printf("\n");
	}

	return 0;
}
