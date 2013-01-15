/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>

using namespace std;

typedef pair<int, int> pii;

const int INF=1<<28;
const int MAXN=1010,MAXM=1010*1010;

int d[MAXN],h[MAXN],first[MAXN],vis[MAXN];
int w[MAXM],l[MAXM],u[MAXM],v[MAXM],next[MAXM];
int n, m, cnt;
int s,e,t;
void Dijkstra();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCount=0;
    while(scanf("%d %d",&n,&m)>0 && (n||m))
    {
        if(nCount)  printf("\n");
        nCount++;
        memset(first,-1,sizeof(first));
        memset(next,-1,sizeof(next));
        cnt=0;
        for(int i=0;i<m;i++)
        {
            scanf("%d %d %d %d",&u[cnt],&v[cnt],&l[cnt],&w[cnt]);
            if(l[cnt]==-1)
                l[cnt]=INF;
            next[cnt]=first[u[cnt]];
            first[u[cnt]]=cnt;
            u[cnt+1]=v[cnt];
            v[cnt+1]=u[cnt];
            l[cnt+1]=l[cnt];
            w[cnt+1]=w[cnt];
            next[cnt+1]=first[u[cnt+1]];
            first[u[cnt+1]]=cnt+1;
            cnt+=2;
        }
        scanf("%d %d %d",&s,&e,&t);
        Dijkstra();
        printf("Case %d:\n",nCount);
        if(d[e]==INF)
        {
            printf("cannot reach destination\n");
        }
        else
        {
            printf("maximum height = %d\n",h[e]);
            printf("length of shortest route = %d\n",d[e]);
        }
    }
    return 0;
}

void Dijkstra()
{
    memset(vis,0,sizeof(vis));
    for(int i=0;i<=n;i++)   h[i]=0;
    priority_queue<pii,vector<pii>,less<pii> > qq;
    h[s]=t;
    qq.push(make_pair(h[s],s));
    while(!qq.empty())
    {
        int x=(qq.top()).second;qq.pop();
        if(vis[x])  continue;
        vis[x]=1;
        for(int y=first[x];y!=-1;y=next[y])
        {
            if(h[v[y]]< min(h[x],l[y]))
            {
                h[v[y]]=min(h[x],l[y]);
                qq.push(make_pair(h[v[y]],v[y]));
            }
        }
    }

    priority_queue<pii,vector<pii>,greater<pii> > q;
    memset(vis,0,sizeof(vis));
    for(int i=0;i<=n;i++)   d[i]=INF;
    d[s]=0;
    q.push(make_pair(d[s],s));
    while(!q.empty())
    {
        int x=(q.top()).second;q.pop();
        if(vis[x])  continue;
        vis[x]=1;
        for(int y=first[x];y!=-1;y=next[y])
        {
            if(d[v[y]]>d[x]+w[y] && (h[e]<=min(h[x],l[y])))
            {
                d[v[y]]=d[x]+w[y];
                q.push(make_pair(d[v[y]],v[y]));
            }
        }
    }
}
