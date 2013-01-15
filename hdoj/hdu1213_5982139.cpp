/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

const int MAXN=1010;

int vis[MAXN];
int v[MAXN];
int p[MAXN];
int n,m;

int find(int x){return p[x]==-1?x:(p[x]=find(p[x]));}

void unionset(int x,int y)
{
    x=find(x);
    y=find(y);
    if(x!=y)
    {
        p[x]=y;
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r",stdin);
#endif

    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %d",&n,&m);
        memset(p,-1,sizeof(p));
        memset(vis,0,sizeof(vis));
        memset(v,0,sizeof(v));
        for(int i=0;i<m;i++)
        {
            int a,b;
            scanf("%d %d",&a,&b);
            vis[a]=vis[b]=1;
            unionset(a,b);
        }
        int ans=n;
        for(int i=1;i<=n;i++)
        {
            if(vis[i])
            {
                int t=find(i);
                if(!v[t])
                {
                    v[t]=1;
                }
                else
                    ans--;

            }
        }
        printf("%d\n",ans);
    }

    return 0;
}
