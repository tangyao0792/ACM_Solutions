#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

const int MAXN=10010,MAXM=100010;
const int INF=1<<28;
int cap[MAXM],flow[MAXM],u[MAXM],v[MAXM],next[MAXM];
int first[MAXN],l[MAXN],fa[MAXN];
int cnt,s,a,k,m;            //s行a列

void add(int from, int to)
{
    u[m]=from;
    v[m]=to;
    cap[m]=1;
    next[m]=first[u[m]];
    first[u[m]]=m;
    m++;

    v[m]=from;
    u[m]=to;
    cap[m]=0;
    next[m]=first[u[m]];
    first[u[m]]=m;
    m++;
}

bool bfs()
{
    memset(fa,-1,sizeof(fa));
    memset(l,0,sizeof(l));
    queue<int> q;
    l[0]=INF;
    q.push(0);
    while(!q.empty())
    {
        int x=q.front();q.pop();
        for(int e=first[x];e!=-1;e=next[e])
        {
            if(!l[v[e]] && cap[e]>flow[e])
            {
                l[v[e]]=min(l[x],cap[e]-flow[e]);
                fa[v[e]]=e;
                if(v[e]==1) return true;
                q.push(v[e]);
            }
        }
    }
    return false;
}

int EK()
{
    int f=0;
    while(bfs())
    {
        f+=l[1];
        for(int t=fa[1];t!=-1;t=fa[u[t]])
        {
            flow[t]+=l[1];
            if(t%2==0)
                flow[t+1]-=l[1];
            else
                flow[t-1]-=l[1];
        }
    }
    //printf("%d    ",f);
    return f;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
   // freopen("out.txt", "w",stdout);
#endif
    int nCase;
    scanf("%d",&nCase);
    while(nCase--)
    {
        scanf("%d %d %d",&s,&a,&k);
        memset(cap,0,sizeof(cap));
        memset(flow,0,sizeof(flow));
        memset(first,-1,sizeof(first));
        memset(next,-1,sizeof(next));

        cnt=1;
        m=0;

        for(int i=1;i<=s;i++)
            for(int j=1;j<=a;j++)
            {
                add(2*cnt,2*cnt+1);

                if(i<s)
                {
                    add(2*cnt+1,2*(cnt+a));
                    add(2*(cnt+a)+1,2*cnt);
                }
                if(j<a)
                {
                    add(2*cnt+1,2*(cnt+1));
                    add(2*(cnt+1)+1,2*cnt);
                }
                cnt++;
            }
        for(int i=1;i<=s;i++)
        {
            int p1=(i-1)*a+1,p2=i*a;
            add(2*p1+1,1);
            add(2*p2+1,1);
        }
        for(int j=1;j<=a;j++)
        {
            int p1=j,p2=s*a-j+1;
            add(2*p1+1,1);
            add(2*p2+1,1);
        }
        for(int i=0;i<k;i++)
        {
            int x,y;
            scanf("%d %d",&x,&y);
            int p=(x-1)*a+y;
            add(0,2*p);
        }
        if(EK()==k)
            printf("possible\n");
        else
            printf("not possible\n");
    }
    return 0;
}
