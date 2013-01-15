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

typedef pair<int,int> pii;
const int INF=1<<28;
const int MAXN=(1<<20)+1;
const int MAXM=110;
int d[MAXN], vis[MAXN], w[MAXM];
int u[MAXM][2], v[MAXM][2];     //[0]加号，[1]减号
int s, e;
int n, m;

void Dijkstra();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase=0;
    while(scanf("%d %d", &n, &m)>0 && m&&n)
    {
        nCase++;
        for(int i=0;i<m;i++)
        {
            char in[25],out[25];
            scanf("%d %s %s",&w[i],in,out);
            u[i][0]=u[i][1]=v[i][0]=v[i][1]=0;
            for(int j=0;j<n;j++)
            {
                u[i][0]=u[i][0]<<1;
                u[i][1]=u[i][1]<<1;
                v[i][0]=v[i][0]<<1;
                v[i][1]=v[i][1]<<1;
                if(in[j]=='+')u[i][0]++;
                if(in[j]=='-')u[i][1]++;
                if(out[j]=='+')v[i][0]++;
                if(out[j]=='-')v[i][1]++;
            }
            v[i][1]=(1<<(n))-1-v[i][1];
        }
        s=e=0;
        for(int i=0;i<n;i++)
        {
            s=(s<<1)+1;
        }
        Dijkstra();
        printf("Product %d\n",nCase);
        if(d[e]<INF)
            printf("Fastest sequence takes %d seconds.\n",d[e]);
        else
            printf("Bugs cannot be fixed.\n");
        printf("\n");
    }
    return 0;
}

void Dijkstra()
{
    int nMax=(1<<n)+1;
    for(int i=0; i<nMax;i++)    d[i]=INF;
    memset(vis,0,sizeof(vis));
    d[s]=0;
    priority_queue<pii,vector<pii>,greater<pii> > q;
    q.push(make_pair(d[s], s));
    while( !q.empty())
    {
        int x=(q.top()).second; q.pop();
        if(vis[x])  continue;
        vis[x]=1;
        for(int y=0;y<m;y++)
        {
            if((x&u[y][0])==u[y][0] && (x&u[y][1])== 0)
            {
                int a=(x|v[y][0])&v[y][1];
                if(d[a]>d[x]+w[y])
                {
                    d[a]=d[x]+w[y];
                    q.push(make_pair(d[a],a));
                }
            }
        }
        if(x==0)    return;
    }
}
