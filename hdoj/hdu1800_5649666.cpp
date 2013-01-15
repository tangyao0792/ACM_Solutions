/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

const int MAXN=3100;
const int MAXM=50;
const int tk=10,tb='0';

int top,n,nMax;
int tree[MAXN*MAXM][MAXM];

void init()
{
    top=1;
    memset(tree[0],0,sizeof(tree[0]));
}
void insert(char *s)
{
    int rt,nxt;
    for(rt=0;*s;rt=nxt,s++)
    {
        nxt=tree[rt][*s-tb];
        if(nxt==0)
        {
            tree[rt][*s-tb]=nxt=top;
            memset(tree[top],0,sizeof(tree[top]));
            top++;
        }
    }
    tree[rt][tk]++;
    if(nMax<tree[rt][tk])
        nMax=tree[rt][tk];
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d",&n)==1)
    {
        nMax=0;
        init();
        for(int i=0;i<n;i++)
        {
            char tmp[50];
            scanf("%s",tmp);
            int nLen=strlen(tmp);
            int j=0;
            while(tmp[j]=='0' && j<nLen-1)j++;
            insert(tmp+j);
        }
        printf("%d\n",nMax);
    }
    return 0;
}
