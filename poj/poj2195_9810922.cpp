#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

const int MAXN=510;
const int INF=1<<28;

int cap[MAXN][MAXN],flow[MAXN][MAXN],d[MAXN],w[MAXN][MAXN];
int mx[MAXN],my[MAXN],hx[MAXN],hy[MAXN],fa[MAXN];

int n,m;
int pm, ph;

int abs(int x){return x>0?x:-x;}
int minmax();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d %d",&n,&m)==2 && n)
    {
        pm=2,ph=2;
        for(int i=2;i<=n+1;i++)
            for(int j=2;j<=m+1;j++)
            {
                char c;
                cin>>c;
                if(c=='m')
                {
                    mx[pm]=i;
                    my[pm]=j;
                    pm++;
                }
                else if(c=='H')
                {
                    hx[ph]=i;
                    hy[ph]=j;
                    ph++;
                }
            }
        for(int i=0;i<=pm+ph+10;i++)
            for(int j=0;j<=pm+ph+10;j++)
                w[i][j]=INF;
        memset(cap,0,sizeof(cap));
        memset(flow,0,sizeof(flow));
        for(int i=2;i<pm;i++)
        {
            cap[0][i]=1;
            w[0][i]=0;
            cap[pm+i][1]=1;
            w[pm+i][1]=0;
        }
        for(int i=2;i<pm;i++)
            for(int j=2;j<ph;j++)
            {
                cap[i][pm+j]=1;
                w[i][pm+j]=abs(mx[i]-hx[j])+abs(my[i]-hy[j]);
                w[pm+j][i]=-w[i][pm+j];
            }
        printf("%d\n",minmax());
    }
    return 0;
}

int minmax()
{
    int c=0;
    queue<int> q;
    bool inq[MAXN];
    for(;;)
    {
        memset(inq,false,sizeof(inq));
        memset(fa,-1,sizeof(fa));
        for(int i=0;i<=pm+ph+10;i++)    d[i]=INF;
        d[0]=0;
        q.push(0);
        while(!q.empty())
        {
            int x=q.front();
            q.pop();
            inq[x]=false;
            for(int v=0;v<=pm+ph+10;v++)
            {
                if(d[v]>d[x]+w[x][v] && cap[x][v]>flow[x][v])
                {
                    d[v]=d[x]+w[x][v];
                    fa[v]=x;
                    if(!inq[v])
                    {
                       inq[v]=true;
                       q.push(v);
                    }
                }
            }
        }
        if(d[1]==INF)   break;
        int a=INF;
        for(int t=1;t!=0;t=fa[t])
            a=min(a,cap[fa[t]][t]-flow[fa[t]][t]);
        if(a==0)    break;
        c+=d[1];
        for(int t=1;t!=0;t=fa[t])
        {
            flow[fa[t]][t]+=a;
            flow[t][fa[t]]-=a;
        }
    }
    return c;
}
