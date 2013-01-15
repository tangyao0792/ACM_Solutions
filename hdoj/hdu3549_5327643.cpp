/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>
#include<queue>

using namespace std;

int n,m;

int cap[20][20], flow[20][20], a[20], fa[20];

int EK();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase, iCase;
    scanf("%d", &nCase);
    for(iCase= 1;iCase<=nCase;iCase++)
    {
        memset(flow,0,sizeof(flow));
        memset(cap,0,sizeof(cap));
        scanf("%d %d",&n,&m);
        for(int i=0;i<m;i++)
        {
            int x, y, w;
            scanf("%d %d %d",&x,&y,&w);
            cap[x][y]+=w;
        }
        printf("Case %d: %d\n",iCase,EK());
    }
}

int EK()
{
    int ans = 0;
    while(1)
    {
        memset(a,0,sizeof(a));
        memset(fa,-1,sizeof(fa));
        queue<int> q;
        a[1] = 1<<28;
        q.push(1);
        while( !q.empty())
        {
            int cur=q.front();
            q.pop();
            for(int i=1;i<=n;i++)
            {
                if(!a[i] && cap[cur][i]>flow[cur][i])
                {
                    a[i]=min(a[cur],cap[cur][i]-flow[cur][i]);
                    fa[i]=cur;
                    q.push(i);
                }
            }
        }
        if(a[n]==0)    break;
        for(int i=n;i!=1;i=fa[i])
        {
            flow[fa[i]][i] += a[n];
            flow[i][fa[i]] -= a[n];
        }
        ans += a[n];
    }
    return ans;
}
