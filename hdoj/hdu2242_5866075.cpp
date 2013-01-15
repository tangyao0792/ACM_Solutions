/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)

const int MAXN=10010;
const int MAXM=40010;
const int INF=1<<28;

int first[MAXN],dp[MAXN],w[MAXN],id[MAXN],vis[MAXN];
int dfn[MAXN],low[MAXN],s[MAXN],sp;
int v[MAXM],next[MAXM],out[MAXM];   //out[i]==1±íê&#190;±&#223;i±&#187;è￥μ&#244;
int nf[MAXN],nv[MAXM],nn[MAXM];
int n,m,cnt,nIndex,nscc,ncnt,sum;

int abs(int x){return x>0?x:-x;}

void addedge(int x,int y)
{
    v[cnt]=y;
    next[cnt]=first[x];
    first[x]=cnt++;
}
void addNewEdge(int x,int y)
{
    nv[ncnt]=y;
    nn[ncnt]=nf[x];
    nf[x]=ncnt++;
}

void tarjan(int root,int fa)
{
    dfn[root]=low[root]=nIndex++;
    vis[root]=1;
    s[sp++]=root;
    int flag=0;
    for(int e=first[root];e!=-1;e=next[e])
    {
        int x=v[e];
        if(x==fa && flag==0)
        {
            flag=1;
            continue;
        }
        if(!dfn[x])
        {
            tarjan(x,root);
            low[root]=min(low[root],low[x]);
        }
        else if(vis[x]==1)
        {
            low[root]=min(low[root],dfn[x]);
        }
        if(dfn[root]<low[x])
        {
            out[e]=1;
        }
    }
    if(low[root]==dfn[root])
    {
        int t;
        do
        {
            t=s[--sp];
            vis[t]=2;
        }while(t!=root);
    }
}

int dfs(int root,int fa)
{
    if(id[root])    return 0;
    int ans=0;
    id[root]=nscc;
    for(int e=first[root];e!=-1;e=next[e])
    {
        if(out[e])  continue;
        int x=v[e];
        if(x==fa)   continue;

        ans+=dfs(x,root);
    }
    return ans+w[root];
}


void treedp(int root,int fa)
{
    if(vis[root])   return;
    vis[root]=1;
    for(int e=nf[root];e!=-1;e=nn[e])
    {
        int x=nv[e];
        if(x==fa)   continue;

        treedp(x,root);
        dp[root]+=dp[x];
    }
}

void solve()
{
    nIndex=nscc=1;
    sp=0;
    memset(dfn,0,sizeof(dfn));
    memset(out,0,sizeof(out));
    memset(vis,0,sizeof(vis));

    for(int i=0;i<n;i++)
        if(!dfn[i])
            tarjan(i,-1);

    memset(id,0,sizeof(id));

    for(int i=0;i<n;i++)
    {
        if(!id[i])
        {
            int tmp=dfs(i,-1);
            dp[id[i]]=tmp;
            nscc++;
        }
    }

    if(nscc==2)
    {
        printf("impossible\n");
        return;
    }

    memset(vis,0,sizeof(vis));
    memset(nf,-1,sizeof(nf));

    for(int i=0;i<n;i++)
    {
        for(int e=first[i];e!=-1;e=next[e])
        {
            if(id[i]!=id[v[e]] && !out[e])
            {
                addNewEdge(id[i],id[v[e]]);
                addNewEdge(id[v[e]],id[i]);
            }
        }
    }

    treedp(1,-1);

    int ans=INF;

    for(int i=1;i<nscc;i++)
    {
        int tmp=abs(sum-2*dp[i]);
        ans=min(ans,tmp);
    }
    printf("%d\n",ans);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif

    while(scanf("%d %d",&n,&m)==2)
    {
        memset(first,-1,sizeof(first));
        cnt=ncnt=0;
        sum=0;
        for(int i=0;i<n;i++)
        {
            scanf("%d",&w[i]);
            sum+=w[i];
        }
        for(int i=0;i<m;i++)
        {
            int x,y;
            scanf("%d %d",&x,&y);
            addedge(x,y);addedge(y,x);
        }
        solve();
    }
    return 0;
}
