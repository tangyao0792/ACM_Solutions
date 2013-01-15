/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif

    int n,k,t;
    while(scanf("%d",&n)==1 && n)
    {
        scanf("%d",&k);
        for(int i=2;i<=n;i++)
        {
            scanf("%d",&t);
            k^=t;
        }
        if(!k)
            printf("Grass Win!\n");
        else
            printf("Rabbit Win!\n");
    }

    return 0;
}
