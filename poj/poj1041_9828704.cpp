#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int MAXN=50 ,MAXM=4000;

struct edge
{
    int u,v,w;
}e[MAXM];

int first[MAXN],next[MAXM],d[MAXN],v[MAXN];
int cnt;
int s[MAXM],sp,vis[MAXM];

bool comp(edge a, edge b){return a.w>b.w;}
bool judge()
{
    for(int i=0;i<MAXN;i++)
        if(v[i]&&d[i]%2!=0)
            return false;

    return true;
}

void Euler(int u)
{
    for(int x=first[e[u].v];x!=-1;x=next[x])
    {
        if(!vis[e[x].w])
        {
            vis[e[x].w]=1;
            Euler(x);
            s[sp++]=x;
        }
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int x,y,z;
    while(scanf("%d %d",&x,&y)==2 && x&&y)
    {
        scanf("%d",&z);
        memset(d,0,sizeof(d));
        memset(v,0,sizeof(v));
        int start=min(x,y);
        cnt=0;
        e[cnt].u=x;
        e[cnt].v=y;
        e[cnt].w=z;
        cnt++;
        e[cnt].v=x;
        e[cnt].u=y;
        e[cnt].w=z;
        cnt++;
        v[x]=v[y]=1;
        d[x]++;
        d[y]++;
        while(scanf("%d %d",&x,&y)==2 && x&&y)
        {
            scanf("%d",&z);
            e[cnt].u=x;
            e[cnt].v=y;
            e[cnt].w=z;
            cnt++;
            e[cnt].v=x;
            e[cnt].u=y;
            e[cnt].w=z;
            cnt++;
            v[x]=v[y]=1;
            d[x]++;
            d[y]++;
        }
        if(!judge())
            printf("Round trip does not exist.\n");
        else
        {
            sort(e,e+cnt,comp);
            memset(first,-1,sizeof(first));
            memset(next,-1,sizeof(next));
            for(int i=0;i<cnt;i++)
            {
                next[i]=first[e[i].u];
                first[e[i].u]=i;
            }
            memset(vis,0,sizeof(vis));
            sp=0;
            for(int x=first[start];x!=-1;x=next[x])
            {
                if(!vis[e[x].w])
                {
                    vis[e[x].w]=1;
                    Euler(x);
                    s[sp++]=x;
                }
            }
           // printf("%d",e[s[sp-1]].w);
            for(int i=sp-1;i>=0;i--)
                printf("%d ",e[s[i]].w);
            printf("\n");
        }
    }
    return 0;
}
