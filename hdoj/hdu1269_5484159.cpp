/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

#define min(a,b) (a<b?a:b)

const int MAXN=10010;
const int MAXM=100010;

int first[MAXN],dfn[MAXN],low[MAXN],s[MAXN],sp;
int next[MAXM],u[MAXM],v[MAXM];
bool mark[MAXN];
int n,m,nIndex,nscc,cnt;

void tarjan(int x)
{
    dfn[x]=low[x]=nIndex++;
    s[sp++]=x;
    mark[x]=true;
    for(int e=first[x];e!=-1;e=next[e])
    {
        int y=v[e];
        if(!dfn[y])
        {
            tarjan(y);
            low[x]=min(low[x],low[y]);
        }
        else if(mark[y])
        {
            low[x]=min(low[x],dfn[y]);
        }
    }
    if(dfn[x]==low[x])
    {
        int t;
        do
        {
            t=s[--sp];
            mark[t]=false;
        }while(t!=x);
        nscc++;
    }
}

int solve()
{
    memset(mark,0,sizeof(mark));
    memset(dfn,0,sizeof(dfn));
    nIndex=nscc=sp=1;
    for(int i=1; i<=n;i++)
        if(!dfn[i])
            tarjan(i);

    return nscc;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d %d",&n,&m)==2 && !(!n && !m))
    {
        cnt=0;
        memset(first,-1,sizeof(first));
        for(int i=0;i<m;i++)
        {
            scanf("%d %d",&u[cnt],&v[cnt]);
            next[cnt]=first[u[cnt]];
            first[u[cnt]]=cnt;
            cnt++;
        }
        if(solve()==2)
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}
