/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>

int main()
{
    int n;
    while(scanf("%d",&n)==1 && n)
    {
        int ans=0;
        for(int i=0;i<n;i++)
        {
            int tmp;
            scanf("%d",&tmp);
            ans^=tmp;
        }
        if(ans)
            printf("Rabbit Win!\n");
        else
            printf("Grass Win!\n");
    }

    return 0;
}
