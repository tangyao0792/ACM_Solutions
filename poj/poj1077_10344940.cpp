#include<cstdio>
#include<iostream>
#include<queue>
#include<cstring>

using namespace std;

struct node
{
	int pos;
	int g,h,num[9];
	node(int pp,int gg,int hh,int a[9])
	{
		pos=pp;
		g=gg;h=hh;
		for(int i=0;i<9;i++)
			num[i]=a[i];
	}
	bool operator<(const node& x)const
	{
		return g+h>x.g+x.h;
	}
};

const int MAXN=362885;

int hash[MAXN],pre[MAXN],dir[MAXN],b[9]={1,1,2,6,24,120,720,5040,40320};
char d[5]="udlr";


inline int abs(int x){return x>0?x:-x;}

int Hash(int num[9])
{
	int ans=0,tmp;
	for(int i=0;i<9;i++)
	{
		tmp=0;
		for(int j=i+1;j<9;j++)
			if(num[i]>num[j])
				tmp++;
		ans+=tmp*b[num[i]];
	}
	return ans;
}

int cal(int num[9])			//calculate the distance
{
	int ans=0;
	for(int i=0;i<9;i++)
		ans+=abs((num[i]+8)%9%3-i%3)+abs((num[i]+8)%9/3-i/3);
	return ans;
}

void dfs(int x)
{
	if(pre[x]==-1)	return ;
	dfs(pre[x]);
	putchar(d[dir[x]]);
}

void swap(int &a,int &b)
{
	int tmp=a;
	a=b;
	b=tmp;
}

int Astar(node st)
{
	priority_queue<node> q;
	int num[9],h;
	q.push(st);
	while(!q.empty())
	{
		node x=q.top();
		q.pop();

		memcpy(num,x.num,sizeof(num));
		int f=Hash(num);

		if(hash[f]) continue;
		hash[f]=1;

		if(cal(num)==0)
			return f;
		int pos=x.pos;

		if(pos/3)
		{
			swap(num[pos],num[pos-3]);
			if(!hash[h=Hash(num)])
			{
				pre[h]=f;
				dir[h]=0;
				q.push(node(pos-3,x.g+1,cal(num),num));
			}
			swap(num[pos],num[pos-3]);
		}
		if(pos/3 != 2)
		{
			swap(num[pos],num[pos+3]);
			if(!hash[h=Hash(num)])
			{
				pre[h]=f;
				dir[h]=1;
				q.push(node(pos+3,x.g+1,cal(num),num));
			}
			swap(num[pos],num[pos+3]);
		}

		if(pos%3)
		{
			swap(num[pos],num[pos-1]);
			if(!hash[h=Hash(num)])
			{
				pre[h]=f;
				dir[h]=2;
				q.push(node(pos-1,x.g+1,cal(num),num));
			}
			swap(num[pos],num[pos-1]);
		}

		if(pos%3!=2)
		{
			swap(num[pos],num[pos+1]);
			if(!hash[h=Hash(num)])
			{
				pre[h]=f;
				dir[h]=3;
				q.push(node(pos+1,x.g+1,cal(num),num));
			}
			swap(num[pos],num[pos+1]);
		}
	}
	return -1;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
    memset(pre,-1,sizeof(pre));
	int num[9];
	int pos;
	for(int i=0;i<9;i++)
	{
		char c;
		cin>>c;
		if(c=='x')
		{
			pos=i;
			num[i]=0;
		}
		else
			num[i]=c-'0'+0;
	}

	int tmp=0;
	for(int i=0;i<9;i++)
		for(int j=i+1;j<9;j++)
			if(num[j] && num[j]<num[i])
				tmp++;
	if(tmp&1)
		puts("unsolvable");
	else
	{
		int ans=Astar(node(pos,0,cal(num),num));
		if(ans!=-1)
		{
			dfs(ans);
			puts("");
		}
		else
            puts("unsolvable");
	}
	return 0;
}
