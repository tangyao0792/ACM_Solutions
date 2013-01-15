#include<cstdio>
#include<iostream>
#include<cstring>
#include<map>
#include<queue>

using namespace std;

const int MAXN=510;
const int INF=1<<28;

int cap[MAXN][MAXN],flow[MAXN][MAXN],a[MAXN],fa[MAXN];
int n,k,cnt;
map<string, int> m;

int EK();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("C.3.dat", "r", stdin);
#endif
    int nCase;
    cin>>nCase;
    while(nCase--)
    {
        memset(cap,0,sizeof(cap));
        memset(flow,0,sizeof(flow));
        cin>>n;
        m.clear();
        cnt=1;
        for(int i=1;i<=n;i++)
        {
            string tmp;
            cin>>tmp;
            if(m.count(tmp)==0)
            {
                m[tmp]=cnt;
                cnt++;
            }
            cap[m[tmp]][505]++;
        }
        cin>>k;
        for(int i=1;i<=k;i++)
        {
            string tmp;
            cin>>tmp;
            cin>>tmp;
            if(m.count(tmp)==0)
            {
                m[tmp]=cnt;
                cnt++;
            }
            cap[0][m[tmp]]++;
        }
        int t;
        cin>>t;
        for(int i=1;i<=t;i++)
        {
            string to,from;
            cin>>from>>to;
            if(m.count(to)==0)
            {
                m[to]=cnt;
                cnt++;
            }
            if(m.count(from)==0)
            {
                m[from]=cnt;
                cnt++;
            }
            cap[m[from]][m[to]]=INF;
        }
        cout<<k-EK()<<endl;
        if(nCase)
            cout<<endl;
    }
    return 0;
}

int EK()
{
    queue<int> q;
    int f=0;
    for(;;)
    {
        memset(a,0,sizeof(a));
        memset(fa,-1,sizeof(fa));
        a[0]=INF;
        q.push(0);
        while(!q.empty())
        {
            int x=q.front();
            q.pop();
            for(int v=0;v<=505;v++)
            {
                if(!a[v] && cap[x][v]>flow[x][v])
                {
                    a[v]=min(a[x],cap[x][v]-flow[x][v]);
                    fa[v]=x;
                    q.push(v);
                }
            }
        }

        if(a[505]==0)   break;
        f+=a[505];

        for(int t=505;t!=0;t=fa[t])
        {
            flow[fa[t]][t]+=a[505];
            flow[t][fa[t]]-=a[505];
        }
    }
    return f;
}
