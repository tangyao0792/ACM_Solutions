#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    __int64 weight;
    int parent;
}HTNode, *HuffmanTree;

int cmp(const void *a, const void *b);
__int64 CreateHT(HuffmanTree &HT,int n, int w[]);
void swap(HTNode & HT1, HTNode &HT2);

int main()
{
    int n;

   scanf("%d",&n);
    int *w = (int*)malloc(sizeof(HTNode) * n);

    for(int i = 0; i < n ; i++)
    {
        scanf("%d",w+i);
    }

    HuffmanTree HT;
    __int64 sum = CreateHT(HT,n,w);
    printf("%I64d\n",sum);
    return 0;
}
__int64 CreateHT(HuffmanTree &HT,int n, int w[])
{
    int i;
    int m = 2 * n - 1;
    HT = (HuffmanTree)malloc(sizeof(HTNode) * m);

    for(i = 0; i < n; i++)
    {
        HT[i].weight = w[i];
        HT[i].parent = -1;
    }
    qsort(HT, n, sizeof(HTNode),cmp);
    __int64 sum = 0;

    for(int j = 0; i < m; i++, j+= 2)
    {
        HT[i].weight = HT[j].weight + HT[j+1].weight;
        sum += HT[i].weight;
        HT[i].parent = -1;
        for(int k = i;k > 0 && HT[k].weight < HT[k-1].weight;
         k--)
        {
            swap(HT[k],HT[k-1]);
        }
    }
    return sum;
}
void swap(HTNode &HT1, HTNode &HT2)
{
    HTNode temp = HT1;
    HT1 = HT2;
    HT2 = temp;
}
int cmp(const void *a, const void *b)
{
    if(((HuffmanTree)a)->weight > ((HuffmanTree)b)->weight)
    {
        return 1;
    }
    return -1;
}
