#include<cstdio>
#include <stdlib.h>
#include<cstring>
#include<cmath>
#define eps 1e-8
#define zero(x) (((x)>0?(x):-(x))<eps)

int n,cnt;
struct point{double x,y;}p[20],pt[20],convex[20];
double dp[1<<17];
double extra[1<<17];
double v[20],l[20];
int num[1<<17];

double distances(point p1,point p2){
return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

//计算 cross product (P1-P0)x(P2-P0)
double xmult(point p1,point p2,point p0){
return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
//graham 算法顺时针构造包含所有共线点的凸包,O(nlogn)
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
//构造凸包接口函数,传入原始点集大小 n,点集 p(p 原有顺序被打乱!)
//返回凸包大小,凸包的点在 convex 中
//参数 maxsize 为 1 包含共线点,为 0 不包含共线点,缺省为 1
//参数 clockwise 为 1 顺时针构造,为 0 逆时针构造,缺省为 1
//在输入仅有若干共线点时算法不稳定,可能有此类情况请另行处理!
//不能去掉点集中重合的点
point temp[20];
int graham(int n,point* p,point* convex,int maxsize=1,int dir=1){
//point* temp=new point[n];
int s,i;
_graham(n,p,s,temp);
for (convex[0]=temp[0],n=1,i=(dir?1:(s-1));dir?(i<s):i;i+=(dir?1:-1))
if (maxsize||!zero(xmult(temp[i-1],temp[i],temp[(i+1)%s])))
convex[n++]=temp[i];
//delete []temp;
return n;
}

double getlength(int n,point *p)
{
    if(n==1)    return 0;
	double ans=0;
	for(int i=0;i<n;i++)
		ans+=distances(p[i],p[(i+n+1)%n]);
	return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	int nCase=1;
	while(scanf("%d",&n)==1 && n)
	{
		printf("Forest %d\n",nCase++);
		for(int i=0;i<n;i++)
		{
			scanf("%lf %lf %lf %lf",&p[i].x,&p[i].y,&v[i],&l[i]);
		}
		int pp=-1;
		int size=1<<(n);
		for(int i=1;i<size;i++)
		{
			cnt=0;
			double val=0;
			double len=0;
			int ncnt=0;
			bool flag=false;
			for(int j=0;j<n;j++)
			{
				if(!(i&(1<<j)))
					pt[cnt++]=p[j];
				else
				{
					ncnt++;
					len+=l[j];
					val+=v[j];
					if(pp!=-1 && val>dp[pp]+eps)
					{
					    flag=true;
					    break;
					}
				}
			}
			if(flag)    continue;
			if(cnt==0)  continue;

			int tmp;
			if(cnt==2 || cnt==1)
			{
			    for(int k=0;k<cnt;k++)
                    convex[k]=pt[k];
                tmp=cnt;
			}
			else
                tmp=graham(cnt,pt,convex);
			double dist=getlength(tmp,convex);
			dp[i]=val;
			extra[i]=len-dist;
			num[i]=ncnt;
			if(pp==-1 && extra[i]>eps)
			{
			    pp=i;
			    continue;
			}
			if(extra[i]<-eps)   continue;
			if(dp[pp]>dp[i]+eps)
			{
			    pp=i;
			}
			else if(dp[pp]<dp[i]-eps){}
			else
			{
			    if(num[pp]>num[i])
                    pp=i;
			}
		}

		printf("Cut these trees:");
		for(int i=0;i<n;i++)
		{
			if(pp&(1<<i))
				printf(" %d",i+1);
		}
		printf("\nExtra wood: %.2f\n\n",extra[pp]);

	}

	return 0;
}
