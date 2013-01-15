#include<stdio.h>
#include<string.h>
void make_next();
    char a[1000010];
    int next[1000010];

int main()
{

    int n;
    int count = 0;
    while( scanf("%d",&n) > 0 && n != 0)
    {
        count++;
        scanf("%s",a);
        printf("Test case #%d\n",count);
        make_next();
        int length = strlen(a);
        for(int i = 1; i < length+1; i++)
        {
            if(((i) %( i - next[i])== 0 &&(next[i] != 0)))
            {
                printf("%d %d\n",i,(i)/(i-next[i]));
            }
        }
        printf("\n");
    }
    return 0;
}

void make_next()
{
    int length = strlen(a);
    next[0] = -1;
    int i = 0;
    int j = -1;
    while(i < length)
    {
        if(j == -1 || a[i] == a[j])
        {
            i++;
            j++;
            next[i] = j;
        }
        else
        {
            j = next[j];
        }
    }
    i++;
    j++;
    next[i] = j;
}
