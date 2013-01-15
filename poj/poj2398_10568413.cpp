#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>

using namespace std;

const int MAXN=1010;

int num[MAXN],times[MAXN];
int n,m,x1,x2,y1,y2;
struct line
{
    int u,l;
}lines[MAXN];
inline int isleft(int x,int y,int x1,int y1,int x2,int y2)
{
	x-=x2;y-=y2;
	int px=x1-x2;
	int py=y1-y2;
	return x*py-y*px<0;
}
bool comp(line a,line b)
{
    if(a.u==b.u)
        return a.l<b.l;
    return a.u<b.u;
}

int get()
{
	int x,y;
	scanf("%d %d",&x,&y);
	if(isleft(x,y,lines[0].u,y1,lines[0].l,y2))
		return 0;
	if(isleft(x,y,lines[n-1].u,y1,lines[n-1].l,y2)==0)
		return n;

	int ll=1,rr=n-1;
	while(ll<=rr)
	{
		int mid=(ll+rr)>>1;
		int tmp1=isleft(x,y,lines[mid].u,y1,lines[mid].l,y2);
		int tmp2=isleft(x,y,lines[mid+1].u,y1,lines[mid+1].l,y2);
		if(tmp1==1 && tmp2==0)
			return mid;

		if(tmp1==1 && tmp2==1)
			rr=mid-1;
		else
			ll=mid+1;
	}
	return ll;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
	while(scanf("%d",&n)==1 && n)
	{
		printf("Box\n");
		scanf("%d %d %d %d %d",&m,&x1,&y1,&x2,&y2);
		for(int i=0;i<n;i++)
			scanf("%d %d",&lines[i].u,&lines[i].l);
		sort(lines,lines+n,comp);
		memset(num,0,sizeof(num));
		memset(times,0,sizeof(times));

		for(int i=0;i<m;i++)
			num[get()]++;
		for(int i=0;i<=n;i++)
            if(num[i])
                times[num[i]]++;
		for(int i=0;i<=n;i++)
		{
			if(times[i]>0)
				printf("%d: %d\n",i,times[i]);
		}
	}
	return 0;
}
