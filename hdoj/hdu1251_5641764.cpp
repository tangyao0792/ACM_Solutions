/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

const int N=500000;

const int tk=26,tb='a';

int top,tree[N][tk+1];

void init()
{
    top=1;
    memset(tree[0],0,sizeof(tree[0]));
}

int sear(char *s)
{
    for(int rt=0;rt=tree[rt][*s-tb];)
        if(*(++s)==0)   return tree[rt][tk];

    return 0;
}

void insert(char *s)
{
    int rt,nxt;
    for(rt=0;*s;rt=nxt,++s)
    {
        tree[rt][tk]++;
        nxt=tree[rt][*s-tb];
        if(nxt==0)
        {
            tree[rt][*s-tb]=nxt=top;

            memset(tree[top],0,sizeof(tree[top]));
            top++;
        }
    }
    tree[rt][tk]++;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    char str[100];
    init();
    while(gets(str) && strlen(str)!=0)
    {
        insert(str);
    }

    while(gets(str))
    {
        printf("%d\n",sear(str));
    }
    return 0;
}
