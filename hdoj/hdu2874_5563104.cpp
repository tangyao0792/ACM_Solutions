/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>
#include<cmath>

#define maxrmq(a,b) (height[r[a]]>height[r[b]]?a:b)
#define minrmq(a,b) (height[r[a]]<height[r[b]]?a:b)

const int MAXN=10010;
const int MAXM=2*10010;
const int MAXQ=1000010;

struct edge
{
    int u,v,w,next;
}e[MAXM];

int dp[20][MAXN*5];
int first[MAXN],vis[MAXN],pos[MAXN];
int r[MAXN*5];
int dis[MAXN],height[MAXN];
int n,m,c,cnt,nIndex;

void addedge(int x,int y,int w)
{
    e[cnt].u=x;e[cnt].v=y;e[cnt].w=w;
    e[cnt].next=first[x];
    first[x]=cnt++;
}
void dfs(int u,int d,int h)
{
    vis[u]=1;
    dis[u]=d;
    height[u]=h;
    if(pos[u]==-1)
        pos[u]=nIndex;
    r[nIndex++]=u;
    for(int i=first[u];i!=-1;i=e[i].next)
    {
        int v=e[i].v;
        if(!vis[v])
        {
            dfs(v,d+e[i].w,h+1);
            r[nIndex++]=u;
        }
    }

}

void SparseTable()
{
    for(int i=1;i<nIndex;i++)
        dp[0][i]=i;

    for(int j=1;(1<<j) <nIndex; j++)
        for(int i=1;i+(1<<(j-1)) <nIndex; i++)
            dp[j][i]=minrmq(dp[j-1][i],dp[j-1][i+(1<<(j-1))]);
}

void swap(int &x,int &y)
{
    int tmp=x;
    x=y;
    y=tmp;
}

int get(int x,int y)
{
    if(x>y) swap(x,y);
    int k=int(log(double(y-x+1))/log(2.0));
    return r[minrmq(dp[k][x],dp[k][y-(1<<k)+1])];
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d %d %d",&n,&m,&c)==3)
    {
        memset(vis,0,sizeof(vis));
        memset(first,-1,sizeof(first));
        memset(pos,-1,sizeof(pos));
        nIndex=cnt=0;
        for(int i=0;i<m;i++)
        {
            int x,y,w;
            scanf("%d %d %d",&x,&y,&w);
            addedge(x,y,w);
            addedge(y,x,w);
        }
        for(int i=1;i<=n;i++)
        {
            r[nIndex++]=0;
            if(!vis[i])
            {
                dfs(i,1,1);
                r[nIndex++]=0;
            }
        }
        SparseTable();
        for(int i=0;i<c;i++)
        {
            int x,y;
            scanf("%d %d",&x,&y);
            int lca=get(pos[x],pos[y]);
            if(lca==0)
                printf("Not connected\n");
            else
                printf("%d\n",dis[x]+dis[y]-2*dis[lca]);
        }
    }
    return 0;
}
