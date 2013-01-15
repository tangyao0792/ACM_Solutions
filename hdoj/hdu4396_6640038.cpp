/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>

using namespace std;

const int MAXN=5002;
const int MAXM=200200;
const int INF=1<<28;

int first[MAXN],d[MAXN][111];
int next[MAXM],u[MAXM],v[MAXM],cnt,w[MAXM];
int vis[MAXN][111];
int n,m,k;

void init()
{
    memset(vis,0,sizeof(vis));
    memset(first,-1,sizeof(first));
    cnt=0;
}
inline void addedge(int x,int y,int c)
{
    u[cnt]=x;v[cnt]=y;
    w[cnt]=c;
    next[cnt]=first[x];
    first[x]=cnt++;
}


struct node
{
    int c;
    int p;
    int mod;
    bool operator < (const node &t) const
    {
        return c>t.c;
    }
};

int dij(int s,int t)
{
    for(int i=1;i<=n;i++)
        for(int j=0;j<111;j++)
            d[i][j]=INF;
    d[s][0]=0;
    priority_queue<node> q;
    node tmp;
    tmp.c=0;tmp.p=s;tmp.mod=0;
    q.push(tmp);
    while(true)
    {
        if(q.empty())   break;
        tmp=q.top();q.pop();
        if(vis[tmp.p][tmp.mod] )    continue;
        if(tmp.p==t && tmp.mod>=k)
            return tmp.c;

        vis[tmp.p][tmp.mod]=1;
        for(int e=first[tmp.p];e!=-1;e=next[e])
        {
            if(!vis[v[e]][tmp.mod+1])
            {
                if(d[v[e]][tmp.mod+1]>d[tmp.p][tmp.mod]+w[e])
                {
                    d[v[e]][tmp.mod+1]=d[tmp.p][tmp.mod]+w[e];
                    node nt;
                    nt.p=v[e];
                    nt.mod=tmp.mod+1;
                    nt.c=d[v[e]][tmp.mod+1];
                    q.push(nt);
                }
            }
        }
    }
    return -1;
    int ans=INF;
//    for(int i=k;i<111;i++)
//        ans=min(ans,d[t][i]);
//    if(ans==INF)
//        return -1;
    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    while(scanf("%d %d",&n,&m)==2)
    {
        init();
        int a,b,c;
        for(int i=0;i<m;i++)
        {
            scanf("%d %d %d",&a,&b,&c);
            addedge(a,b,c);
            addedge(b,a,c);
        }
        scanf("%d %d %d",&a,&b,&c);
        k=(c-1)/10+1;
        printf("%d\n",dij(a,b));
    }
    return 0;
}
