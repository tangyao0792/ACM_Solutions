#include<iostream>
#include<cstring>
#include<cstdio>

using namespace std;

const int MAXN=5010;

int u[MAXN],l[MAXN],num[MAXN];
int n,m,x1,x2,y1,y2;

int isleft(int x,int y,int x1,int y1,int x2,int y2)
{
	x-=x2;y-=y2;
	int px=x1-x2;
	int py=y1-y2;
	return x*py-y*px<0;
}
int get()
{
	int x,y;
	scanf("%d %d",&x,&y);
	if(isleft(x,y,u[0],y1,l[0],y2))
		return 0;
	if(isleft(x,y,u[n-1],y1,l[n-1],y2)==0)
		return n;

	int ll=1,rr=n-1;
	while(ll<=rr)
	{
		int mid=(ll+rr)>>1;
		int tmp1=isleft(x,y,u[mid],y1,l[mid],y2);
		int tmp2=isleft(x,y,u[mid+1],y1,l[mid+1],y2);
		if(tmp1==1 && tmp2==0)
			return mid;

		if(tmp1==1 && tmp2==1)
			rr=mid-1;
		else
			ll=mid+1;
	}
	return ll;
}

//int get()
//{
//    int x,y;
//    scanf("%d %d",&x,&y);
//    if(isleft(x,y,u[0],y1,l[0],y2))
//		return 0;
//	if(isleft(x,y,u[n-1],y1,l[n-1],y2)==0)
//		return n;
//
//    for(int i=0;i<n;i++)
//    {
//        int tmp1=isleft(x,y,u[i],y1,l[i],y2);
//        int tmp2=isleft(x,y,u[i+1],y1,l[i+1],y2);
//        if(tmp1==0 && tmp2==1)
//            return i+1;
//    }
//    return 0;
//}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
	int cnt=0;
	while(scanf("%d",&n)==1 && n)
	{
		if(cnt)	printf("\n");
		cnt++;
		scanf("%d %d %d %d %d",&m,&x1,&y1,&x2,&y2);
		for(int i=0;i<n;i++)
			scanf("%d %d",&u[i],&l[i]);
		memset(num,0,sizeof(num));

		for(int i=0;i<m;i++)
			num[get()]++;

		for(int i=0;i<=n;i++)
		{
			printf("%d: %d\n",i,num[i]);
		}
	}
	return 0;
}
