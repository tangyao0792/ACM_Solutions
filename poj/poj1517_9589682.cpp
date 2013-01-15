#include<stdio.h>
#include<string.h>
int main()
{
    int i, n;
    double sum, mul;
    char buf[12];
    printf("n e\n");
    printf("- -----------\n");
    for(n = 0; n < 10; n++)
    {

        sum = 0;
        mul = 1;
        for(i = 0; i < n+1; i++)
        {
            mul = 1;
            for(int j = 1; j < i+1;j ++)
            {
                mul *=j;
            }
            sum += (1 / mul);
        }
        sprintf(buf, "%.9lf",sum);
        int length = strlen(buf);
        for(i = length -1; i > -1; i--)
        {
            if(buf[i] != '0' && buf[i] != '.')
            {
                break;
            }

            buf[i] = '\0';
        }
        printf("%d %s\n",n,buf);
    }
    return 0;
}
