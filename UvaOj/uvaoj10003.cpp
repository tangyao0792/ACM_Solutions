#include<cstdio>
#include<cstring>

#define min(a,b) (a>b?b:a)

const int INF=1<<28;

int l, n;
int a[51];
int v[51][51],d[51][51];

int dp(int x, int y)
{
    if(v[x][y])
        return d[x][y];
    v[x][y]=1;
    int nMin=INF;
    if(x+1!=y)
        for(int i=x+1;i<y;i++)
        {
            nMin=min(nMin,dp(x,i)+dp(i,y)+a[y]-a[x]);
        }
    else
        nMin=0;
    return d[x][y]=nMin;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d", &l)==1 && l)
    {
        memset(v,0,sizeof(v));
        memset(d,0,sizeof(d));
        scanf("%d", &n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        a[0]=0;
        a[n+1]=l;
        printf("The minimum cutting is %d.\n",dp(0,n+1));
    }
    return 0;
}
