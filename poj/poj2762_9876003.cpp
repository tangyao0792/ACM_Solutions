#include<cstdio>
#include<cstring>

#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)

const int MAXN=1010;
const int MAXM=6010;

int u[MAXM],v[MAXM],next[MAXM];
int first[MAXN],s[MAXN],sp,dfn[MAXN],low[MAXN],id[MAXN];
int n,m,nscc,index,cnt;

int d[MAXN];
int g[MAXN][MAXN];

bool mark[MAXN];

void tarjan(int x)
{
    dfn[x]=low[x]=index++;
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
            id[t]=nscc;
            mark[t]=false;
        }while(t!=x);
        nscc++;
    }
}

int dp(int x)
{
    if(mark[x]) return d[x];
    mark[x]=true;

    int nMax=0;
    for(int i=1;i<nscc;i++)
        if(g[x][i])
            nMax=max(nMax,dp(i));

    return d[x]=nMax+1;
}

int solve()
{
    sp=0;
    index=1;
    nscc=1;
    memset(mark,0,sizeof(mark));
    memset(dfn,0,sizeof(dfn));
    memset(id,0,sizeof(id));
    memset(d,0,sizeof(d));

    for(int i=1;i<=n;i++)
        if(!dfn[i])
            tarjan(i);

    for(int i=1;i<nscc;i++)
        for(int j=1;j<nscc;j++)
            g[i][j]=0;

    for(int i=1;i<=n;i++)               //所点之后重新建图
        for(int e=first[i];e!=-1;e=next[e])
            if(id[i]!=id[v[e]])
                g[id[i]][id[v[e]]]=1;



    memset(mark,0,sizeof(mark));

    int nMax=-1;
    for(int i=1;i<nscc;i++)
        nMax=max(nMax,dp(i));

    if(nMax==nscc-1)
        return 1;

    return 0;
}

inline void readint(int &ret) {
	char c;
	do {	c = getchar();
	} while(c < '0' || c > '9');
	ret = c - '0';
	while((c=getchar()) >= '0' && c <= '9')
		ret = ret * 10 + ( c - '0' );
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    int nCase;
    scanf("%d",&nCase);
    while(nCase--)
    {
        memset(first,-1,sizeof(first));
        scanf("%d %d",&n,&m);
        cnt=0;
        for(int i=0;i<m;i++)
        {
            int x,y;

            readint(x);readint(y);
            u[cnt]=x;
            v[cnt]=y;
            next[cnt]=first[x];
            first[x]=cnt++;
        }
        if(solve()==1)
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}
