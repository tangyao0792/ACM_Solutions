#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
    int weight;
    int parent;
}HTNode, *HuffmanTree;

void CreateHuffmanTree(HuffmanTree &HT, int n, int w[]);

int main()
{
    int map[27];
    int show[27];
    int len[27];
    char input[1000];
    const char end[] = "END";
    int length, i,  step;

    while(scanf("%s", input) > 0)
    {
        if(strcmp(input, end) == 0)
        {
            break;
        }
        for(i = 0; i < 27; i++)
        {
            map[i] = 0;
        }
        length = strlen(input);
        for(i = 0; i < length; i++)
        {
            if(input[i] == '_')
            {
                map[26]++;
            }
            else
            {
                map[input[i] - 'A']++;
            }
        }
        step = 0;
        for(i = 0; i < 27; i++)
        {
            if(map[i] != 0)
            {
                show[step] = map[i];
                step++;
            }
        }
        HuffmanTree HT;
        CreateHuffmanTree(HT, step, show);
        for(i = 0; i < step; i++)
        {
            int p = HT[i].parent;
            int count = 0;
            while(p != -1)
            {
                p = HT[p].parent;
                count++;
            }
            len[i] = count;
        }
        if(step == 1)
        {
            len[0] = 1;
        }
        int sum = 0;
        for(i = 0; i < step; i++)
        {
            sum += len[i] * show[i];
        }
        double rate =((double)length * 8 / sum);
        printf("%d %d %.1lf\n",length * 8,sum,rate  );

    }
    return 0;
}

void Select(HuffmanTree &HT, int i, int &s1, int &s2)
{
    s1 = s2 = -1;
    int j = 0;
    for(; j < i; j++)
    {
        if(HT[j].parent != -1)
        {
            continue;
        }
        if(s1 == -1)
        {
            s1 = j;
        }
        else if( HT[j].weight < HT[s1].weight)
        {
            s1 = j;
        }
    }
    HT[s1].parent = i;

    for(j = 0; j < i; j++)
    {
        if(HT[j].parent != -1)
        {
            continue;
        }
        if(s2 == -1)
        {
            s2 = j;
        }
        else if( HT[j].weight < HT[s2].weight)
        {
            s2 = j;
        }
    }
    HT[s2].parent = i;
}

void CreateHuffmanTree(HuffmanTree &HT, int n, int w[])
{
    int m = 2 * n - 1;
    HT = (HuffmanTree)malloc(sizeof(HTNode) * m);
    int i = 0;
    for(; i < n; i++)
    {
        HT[i].weight = w[i];
        HT[i].parent = -1;
    }
    for(; i < m; i++)
    {
        HT[i].parent = HT[i].weight = -1;
    }
    int s1, s2;
    for(i = n; i < m; i++)
    {
        Select(HT, i, s1, s2);
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
}
