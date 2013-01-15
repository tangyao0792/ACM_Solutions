/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

const int INF = 1<<28;
int n, m;
int cap[210][210],flow[210][210];
int a[210],fa[210];
long long f;
void ek();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d %d",&m,&n)>0)
    {
        memset(cap,0,sizeof(cap));
        memset(flow,0,sizeof(flow));
        for(int i=0;i<m;i++)
        {
            int x, y, c;
            scanf("%d %d %d",&x,&y,&c);
            cap[x][y]+=c;
        }
        ek();
        cout << f << endl;
    }
    return 0;
}

void  ek()
{
    f = 0;
    queue<int> q;
    memset(fa, 0, sizeof(fa));
    while(1)
    {
        memset(a,0,sizeof(a));
        a[1]=INF;
        q.push(1);
        while( !q.empty())
        {
            int u=q.front();
            q.pop();
            for(int v=1;v<=n;v++)
            {
                if(!a[v]&&flow[u][v]<cap[u][v])
                {
                    a[v]=min(a[u],cap[u][v]-flow[u][v]);
                    fa[v]=u;
                    q.push(v);
                }
            }
        }
        if(a[n]==0)break;
        for(int v=n;v!=1;v=fa[v])
        {
            flow[fa[v]][v]+=a[n];
            flow[v][fa[v]]-=a[n];
        }
        f+=a[n];
    }
}
