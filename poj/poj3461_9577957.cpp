#include<stdio.h>
char word[10010];
char text[1000010];
int next[10010];

void make_next();

int main()
{
    int n;
    int count;
    scanf("%d",&n);
    for(int i = 0; i < n; i++)
    {
        count = 0;
        scanf("%s\n%s",word, text);
        make_next();
        for(int j = 0,k = 0; text[j]; )
        {
            if(word[k] == text[j]|| k == -1)
            {
                k++;
                j++;
            }
            else
            {
                k = next[k];
                continue;
            }
            if(!word[k])
            {
                count++;
                k = next[k];
            }
        }
        printf("%d\n",count);
   }
    return 0;
}

void make_next()
{
    next[0] = -1;
    int i =1;
    int j = -1;
    while(word[i-1])
    {
        if(j == -1 || word[i-1] == word[j])
        {
            i++;
            j++;
            if( word[i-1] != word[j])
            {
                next[i-1] = j;
            }
            else
            {
                next[i-1] = next[j];
            }
        }
        else
        {
            j = next[j];
        }
    }
}
