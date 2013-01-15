#include<stdio.h>
#include<stdlib.h>

typedef struct Pixel
{
    int pos;
    int code;
}Pix;
typedef struct Input
{
    int num;
    int length;
}In;

Pix pix[10000];
In in[1000];
int GetCode(int row, int col, int total, int width);
int abs(int a);
int SearchCode(int row, int col, int width);
int cmp(const void *a, const void * b);
int main()
{
    int width;
    int i, j, k, l;
    int total,posi;
    int a, b, pair;
    int row, col;
    while(scanf("%d", &width)> 0 && width > 0)
    {
        pair = 0;
        total = 0;
        while(scanf("%d %d", &a, &b) && b > 0)
        {
            in[pair].num = a;
            in[pair++].length = b;
            total += b;
        }
        posi = 0;
        l = 0;
        for(k = 0; k < pair+1; k++)
        {
            row = posi / width;
            col = posi % width;
            for(i = row-1; i < row+2; i++)
            {
                for(j = col-1; j < col+2; j++)
                {
                    if(i < 0 ||j < 0 || i > total/width-1|| j > width-1)
                    {
                        continue;
                    }
                    pix[l].pos = i * width +j;
                    pix[l++].code = GetCode(i, j, total, width);
                }
            }
            posi += in[k].length;
        }
        row = (total-1) / width;
        col = (total-1) % width;
        pix[l].pos = row*width+col;
        pix[l++].code = GetCode(row,col,total,width);



        qsort(pix,l-1,sizeof(Pix),cmp);


        printf("%d\n",width);
        int start = 0;
        for(i = 0; i < l-1; i++)
        {
            if(pix[start].code == pix[i].code)
            {
                continue;
            }
            printf("%d %d\n", pix[start].code, pix[i].pos - pix[start].pos);
            start = i;
        }
        printf("%d %d\n",pix[start].code, pix[i].pos - pix[start].pos+1);
        printf("0 0\n");
    }
    printf("0\n");
    return 0;
}
int abs(int a)
{
    if(a < 0)
    {
        return -a;
    }
    return a;
}
int SearchCode(int row, int col, int width)
{
    int pos = row*width + col;
    int i = 0, j = 0;
    while(i < pos+1)
    {
        i += in[j++].length;
    }
    return in[j-1].num;
}
int GetCode(int row, int col, int total, int width)
{
    int max = 0;
    int i, j;
    for(i = row-1; i < row+2; i++)
    {
        for(j = col-1; j < col+2; j++)
        {
            if(i < 0|| j < 0 || i > total/width -1 || j > width-1)
            {
                continue;
            }
            if( max < abs(SearchCode(row, col, width) - SearchCode(i,j,width)))
            {
                max = abs(SearchCode(row, col, width) - SearchCode(i,j,width));
            }
        }
    }
    return max;
}
int cmp(const void *a, const void *b)
{
    Pix *x = (Pix *)a;
    Pix *y = (Pix *)b;
    return (x->pos)- (y->pos);
}
