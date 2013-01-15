/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<iostream>
#include<cstring>
#include<vector>
#include<queue>

using namespace std;

const int MAXM=70010,MAXN=3010;
const long long INF=(1LL)<<54;

typedef pair<long long,int> pii;

int u[MAXM],v[MAXM],next[MAXM];
long long w[MAXM];
long long d[MAXN];
int vis[MAXN];
int first[MAXN], in[MAXM];
vector<int> node[MAXN];                   //保护的城市

int n,m,cnt;

void dij();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase;
    scanf("%d",&nCase);
    while( nCase--)
    {
        memset(first,-1,sizeof(first));
        memset(next,-1,sizeof(next));
        memset(in,0,sizeof(in));
        for(int i=0;i<=n;i++)
            node[i].clear();

        scanf("%d %d",&n,&m);
        cnt=0;
        for(int i=0;i<m;i++)
        {
            int x,y,we;
            scanf("%d %d %d",&x,&y,&we);
            u[cnt]=x;
            v[cnt]=y;
            w[cnt]=we;

            next[cnt]=first[u[cnt]];
            first[u[cnt]]=cnt;
            cnt++;
        }
        for(int i=1;i<=n;i++)
        {
            int x;
            scanf("%d",&x);
            in[i]=x;
            for(int j=0;j<x;j++)
            {
                int k;
                scanf("%d",&k);
                node[k].push_back(i);
            }
        }
        dij();
        cout<<d[n]<<endl;
    }
    return 0;
}

void dij()
{
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)    d[i]=INF;
    d[1]=0;
    priority_queue<pii,vector<pii>,greater<pii> >q;
    q.push(make_pair(d[1],1));
    while(!q.empty())
    {
        int x=(q.top()).second;
        q.pop();
        if(vis[x])    continue;

        vis[x]=1;

        int size=node[x].size();
        for(int i=0;i<size;i++)
        {
            in[node[x][i]]--;
            if(d[node[x][i]]<d[x])
            {
                d[node[x][i]]=d[x];
            }
            if(in[node[x][i]]==0 && d[node[x][i]]<INF)
            {
                q.push(make_pair(d[node[x][i]],node[x][i]));
            }
        }

        for(int e=first[x];e!=-1;e=next[e])
        {
            if(d[v[e]]>d[x]+w[e])
            {
                d[v[e]]=d[x]+w[e];
                if(in[v[e]]==0)
                    q.push(make_pair(d[v[e]],v[e]));
            }
        }
    }
}
