#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>

using namespace std;

const int MAXN=110,MAXM=110;
const char *gt="gt";
const char *lt="lt";
const int INF=1<<28;

int n, m;
int first[MAXN],d[MAXN],cnt[MAXN];
int w[MAXM],u[MAXM],v[MAXM],next[MAXM];

bool SPFA(int s);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    while(scanf("%d %d",&n,&m)>0 &&n&&m)
    {
        memset(first,-1,sizeof(first));
        memset(next,-1,sizeof(next));
        for(int i=0;i<m;i++)
        {
            char op[3];
            int x,y,we;
            scanf("%d %d %s %d",&x,&y,op,&we);
            x++;
            y+=x;
            if(strcmp(op,gt)==0)
            {
                u[i]=x-1;
                v[i]=y;
                w[i]=-we-1;
            }
            else
            {
                u[i]=y;
                v[i]=x-1;
                w[i]=we-1;
            }
            next[i]=first[u[i]];
            first[u[i]]=i;
        }
        bool flag=false;
        for(int i=0;i<=n+1;i++)if(SPFA(i))
            {
                flag = true;
                printf("successful conspiracy\n");
                break;
            }
        if(!flag)
            printf("lamentable kingdom\n");

    }
    return 0;
}

bool SPFA(int s)
{
    queue<int> q;
    bool inq[MAXN];
    memset(inq,0,sizeof(inq));
    memset(cnt,0,sizeof(cnt));
    for(int i=0;i<=n+1;i++)   d[i]=INF;
    d[s]=0;
    q.push(s);
    while(!q.empty())
    {
        int x=q.front();
        q.pop();
        cnt[x]++;
        if(cnt[x]>n+1)  return true;
        inq[x]=false;
        for(int e=first[x];e!=-1;e=next[e])
        {
            if(d[v[e]]>d[x]+w[e])
            {
                d[v[e]]=d[x]+w[e];
                if(!inq[v[e]])
                {
                    inq[v[e]]=true;
                    q.push(v[e]);
                }

            }
        }
    }
    return false;
}
