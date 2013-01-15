#include<stdio.h>
int main()
{
    int i,n,sum;
    printf("PERFECTION OUTPUT\n");
    while(scanf("%d",&n)>0 && n != 0)
    {
        sum = 0;
        for(i = 1; i < n/2 +1; i++)
        {
            if(n % i == 0)
            {
                sum += i;
            }
        }
        printf("%5d  ",n);
        if(sum > n)
        {
            printf("ABUNDANT\n");
        }
        else if(sum == n)
        {
            printf("PERFECT\n");
        }
        else
        {
            printf("DEFICIENT\n");
        }
    }
    printf("END OF OUTPUT");
    return 0;
}
