#include<stdio.h>
#include<string.h>

int g[25][25];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int x, i, j, k;
    int nCase = 0;
    while( scanf("%d", &x) > 0)
    {
        nCase++;
        memset(g, 0, sizeof(g));
        for(i = 0; i < 25; i++)
        {
            for(j = 0; j < 25; j++)
            {
                g[i][j] = 1000;
            }
        }
        for(i = 0; i < 25; i++)
        {
            g[i][i] = 0;
        }
        for(i = 0; i < x; i++)
        {
            scanf("%d", &j);
            g[1][j] = 1;
            g[j][1] = 1;
        }
        for(i = 2; i <= 19; i++)
        {
            scanf("%d", &x);
            for(j = 0; j < x; j++)
            {
                scanf("%d", &k);
                g[i][k] = 1;
                g[k][i] = 1;
            }
        }
        for(k = 1; k <= 20; k++)
        {
            for(i = 1; i <= 20; i++)
            {
                for(j = 1; j <= 20; j++)
                {
                    if(g[i][k] + g[k][j] < g[i][j])
                    {
                        g[i][j] = g[i][k] + g[k][j];
                    }
                }
            }
        }
        printf("Test Set #%d\n", nCase);
        scanf("%d", &x);
        for(i = 0; i < x; i++)
        {
            scanf("%d %d\n", &j, &k);
            printf("%2d to %2d: %d\n",j,k,g[j][k]);
        }
        printf("\n");
    }
    return 0;
}
