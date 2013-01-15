/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
#include<vector>

using namespace std;

const int INF=1<<26;
const int MAXN=210;

int x[MAXN],y[MAXN],r[MAXN],d[3][MAXN],g[MAXN][MAXN],v[MAXN];
int n;

int dis(int i, int j)
{
    int tmp=(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
    if(tmp>(r[i]+r[j])*(r[i]+r[j]))
        return 0;
    return 1;
}

void dij(int s)
{
    for(int i=0;i<n;i++)    d[s][i]=INF;
    memset(v,0,sizeof(v));
    d[s][s]=0;
    typedef pair<int ,int > pii;
    priority_queue<pii,vector<pii>, greater<pii> >q;

    q.push(make_pair(d[s][s],s));

    while(!q.empty())
    {
        int x=q.top().second;q.pop();
        if(v[x])    continue;
        v[x]=1;
        for(int i=0;i<n;i++)
        {
            if(d[s][i]>d[s][x]+g[x][i])
            {
                d[s][i]=d[s][x]+g[x][i];
                q.push(make_pair(d[s][i],i));
            }
        }
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase;
    scanf("%d",&nCase);
    while(nCase--)
    {
        scanf("%d",&n);
        for(int i=0;i<n;i++)
        {
            scanf("%d %d %d",&x[i],&y[i],&r[i]);
        }
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
            {
                if(dis(i,j))
                    g[i][j]=1;
                else
                    g[i][j]=INF;
            }

        dij(0);dij(1);dij(2);
        int ans=INF;
        for(int i=0;i<n;i++)
        {
            ans=min(ans,d[0][i]+d[1][i]+d[2][i]);
        }
        if(ans<INF)
            printf("%d\n",n-1-ans);
        else
            printf("-1\n");
    }
    return 0;
}
