#include<cstdio>
#include<cstring>
#include<cmath>

#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

const int MAXN=50010;

int n,q;
int stMax[MAXN][18],stMin[MAXN][18];

void SparseTable()
{
    for(int j=1;1+(1<<j) <= n; j++)
    {
        for(int i=1;i+(1<<(j-1)) <=n;i++)
        {
            stMax[i][j]=max(stMax[i][j-1],stMax[i+(1<<(j-1))][j-1]);
            stMin[i][j]=min(stMin[i][j-1],stMin[i+(1<<(j-1))][j-1]);
        }
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d %d",&n,&q)==2)
    {
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&stMax[i][0]);
            stMin[i][0]=stMax[i][0];
        }

        SparseTable();

        for(int i=0;i<q;i++)
        {
            int x,y;
            scanf("%d %d",&x,&y);

            int k=int(log(double(y-x+1))/log(2.0));
            int ans=max(stMax[x][k],stMax[y-(1<<k)+1][k]);

            ans-=min(stMin[x][k],stMin[y-(1<<k)+1][k]);
            printf("%d\n",ans);
        }
    }
    return 0;
}
