#include<stdio.h>

int main()
{
    int count = 1;
    int n, hi[100], sum,average, moves;
    int i;
    while(scanf("%d",&n) > 0 && n != 0)
    {
        sum = 0;
        moves = 0;
        for(i = 0; i < n; i++)
        {
            scanf("%d",hi+i);
            sum += hi[i];
        }
        average = sum/n;
        for(i = 0; i < n; i++)
        {
            if(hi[i] > average)
            {
                moves += hi[i] - average;
            }
        }
        printf("Set #%d\n",count);
        printf("The minimum number of moves is %d.\n\n",moves);
        count ++;
    }
    return 0;
}
