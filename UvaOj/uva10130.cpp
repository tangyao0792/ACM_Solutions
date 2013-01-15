#include<cstdio>
#include<cstring>

#define max(a,b) (a>b?a:b)

int w[1010],c[1010],f[1010][35];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase;
    scanf("%d", &nCase);
    while(nCase--)
    {
        memset(f,0,sizeof(f));
        int n;
        scanf("%d", &n);
        for(int i=1;i<=n;i++)
            scanf("%d %d", &w[i],&c[i]);
        //f[i][v]=max(f[i-1][v],f[i-1],[v-c[i]]+w[i])
        for(int i=1;i<=n;i++)
            for(int v=34;v>=0;v--)
                if(v>=c[i])
                    f[i][v]=max(f[i-1][v],f[i-1][v-c[i]]+w[i]);
                else
                    f[i][v]=f[i-1][v];
        int g;
        scanf("%d",&g);
        int sum=0;
        for(int i=0;i<g;i++)
        {
            int x;
            scanf("%d",&x);
            sum+=f[n][x];
        }
        printf("%d\n",sum);
    }
    return 0;
}
