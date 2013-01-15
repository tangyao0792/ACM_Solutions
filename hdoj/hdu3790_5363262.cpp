/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>

using namespace std;

const int INF=1<<28;
const int MAXN=1010,MAXM=100010;
int u[MAXM],v[MAXM],w[MAXM],c[MAXM],d[MAXN],cost[MAXN];
int first[MAXN],next[MAXM];
bool inq[MAXN];

int n,m,s,t,cnt;

void spfa();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d %d",&n,&m)==2&&n&&m)
    {
        memset(first,-1,sizeof(first));
        cnt=0;
        for(int i=0;i<m;i++)
        {
            scanf("%d %d %d %d",&u[cnt],&v[cnt],&w[cnt],&c[cnt]);
            next[cnt]=first[u[cnt]];
            first[u[cnt]]=cnt;
            u[cnt+1]=v[cnt];
            v[cnt+1]=u[cnt];
            w[cnt+1]=w[cnt];
            c[cnt+1]=c[cnt];
            next[cnt+1]=first[u[cnt+1]];
            first[u[cnt+1]]=cnt+1;
            cnt+=2;
        }
        scanf("%d %d",&s,&t);
        spfa();
        printf("%d %d\n",d[t],cost[t]);
    }
    return 0;
}

void spfa()
{
    for(int i=1;i<=n;i++)
    {
        d[i]=INF;
        cost[i]=INF;
    }
    d[s]=0;
    cost[s]=0;
    queue<int> q;
    q.push(s);
    memset(inq,false,sizeof(inq));
    while(!q.empty())
    {
        int x=q.front();
        q.pop();
        inq[x]=false;
        for(int e=first[x];e!=-1;e=next[e])
        {
            if(d[v[e]]>d[x]+w[e])
            {
                d[v[e]]=d[x]+w[e];
                cost[v[e]]=cost[x]+c[e];
                if(!inq[v[e]])
                {
                    inq[v[e]]=true;
                    q.push(v[e]);
                }
            }
            else if(d[v[e]]==d[x]+w[e] && cost[v[e]]>cost[x]+c[e])
            {
                cost[v[e]]=cost[x]+c[e];
                if(!inq[v[e]])
                {
                    inq[v[e]]=true;
                    q.push(v[e]);
                }
            }
        }
    }
}
