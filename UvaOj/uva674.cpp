#include<cstdio>
#include<cstring>

int d[5][7500];
int c[5]={1,5,10,25,50};

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    memset(d,0,sizeof(d));
    d[0][0]=1;

    for(int i=0;i<5;i++)
        for(int v=0;v<=7489;v++)
        {
            if(v>=c[i])
                d[i][v]+=d[i][v-c[i]];
            if(i>=1)
                d[i][v]+=d[i-1][v];
        }
    int n;
    while(scanf("%d",&n)==1)
        printf("%d\n",d[4][n]);
    return 0;
}
