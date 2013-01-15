/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r",stdin);
#endif

    int n,m;
    while(scanf("%d %d",&m,&n)==2)
    {
        if(n>=m)
        {
            for(int i=m;i<=n;i++)
            {
                printf("%d",i);
                if(i!=n)
                    printf(" ");
            }
                printf("\n");
        }
        else if(m%(n+1))
        {
            printf("%d\n",m%(n+1));
        }
        else
        {
            printf("none\n");
        }
    }

    return 0;
}
