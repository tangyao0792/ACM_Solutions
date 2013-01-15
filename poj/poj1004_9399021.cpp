#include <stdio.h>
void main()
{
    int i;
    double sum,money;
    for( i = 0,sum = 0; i < 12 ; i++)
    {
        scanf("%lf" , &money);
        sum += money;
    }
    printf("$%.2lf", sum /12.0);
}
