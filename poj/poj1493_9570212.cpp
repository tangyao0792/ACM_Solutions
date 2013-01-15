#include<stdio.h>

int main()
{
    int n,count,sum;
    int row[13];
    char c;
    int i,j,max;
    while(scanf("%d",&n) > 0 && n != 0)
    {
        max = 0;
        sum = 0;
        for(i = 0; i < n;i ++)
        {
            count= 0;
            for(j = 0; j < 25; j++)
            {
                c = getchar();
                if(c != ' ')
                {
                    count++;
                }
            }
            getchar();
            row[i] = count;
            if(max < count)
            {
                max = count;
            }

        }
        for(i = 0; i < n;i++)
        {
            sum += max-row[i];
        }
        printf("%d\n",sum);


    }
    return 0;
}
