#include<cstdio>
#include<cstring>

const int INF = 1<<28;
const double EPS = 1e-12;

typedef struct
{
    int u,v;
    double r, c;
}E;

E e[510];
double d[510];
int n, m, s,cnt;
double value;

bool bellman();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    while(scanf("%d %d %d %lf",&n,&m,&s,&value)>0)
    {
        memset(d, 0, sizeof(d));
        memset(e, 0, sizeof(e));
        cnt = 0;
        for(int i=0;i<m;i++)
        {
            scanf("%d %d %lf %lf",&e[cnt].u,&e[cnt].v,&e[cnt].r,&e[cnt].c);
            e[cnt+1].u=e[cnt].v;
            e[cnt+1].v=e[cnt].u;
            cnt++;
            scanf("%lf %lf",&e[cnt].r,&e[cnt].c);
            cnt++;
        }
        if(bellman())
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
    }
    return 0;
}

bool bellman()
{
    d[s]=value;
    for(int k=0;k<n-1;k++)
    {
        for(int i=0;i<cnt;i++)
        {
            int x=e[i].u;
            int y=e[i].v;
            if(d[y]<(d[x]-e[i].c)*e[i].r)
            {
                d[y] = (d[x]-e[i].c)*e[i].r;
            }
        }
    }
    for(int i=0;i<cnt;i++)
    {
        int x=e[i].u;
        int y=e[i].v;
        if(d[y]<(d[x]-e[i].c)*e[i].r)
        {
            return true;
        }
    }
    return false;
}
