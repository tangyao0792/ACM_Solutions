#include<cstdio>
#include<cstring>

const int MAXN=100100;
const int MAXM=20;
const int tk=26,tb='a';

char str[MAXN][MAXM];
int tree[MAXN*MAXM][tk+1];
int top,cnt;

void init()
{
    top=1;
    memset(tree[0],0,sizeof(tree[0]));
}
int sear(char *s)
{
    for(int rt=0;rt=tree[rt][*s-tb];)
        if(*(++s)==0)    return tree[rt][tk];
    return 0;
}

void insert(char *s,int rank)
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
    tree[rt][tk]=rank;
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    char line[100];
    char tmp[20];
    cnt=1;
    init();

    while(gets(line) && strlen(line))
    {
        sscanf(line,"%s %s",str[cnt],tmp);
        insert(tmp,cnt);
        cnt++;
    }
    while(gets(line))
    {
        int p=sear(line);
        if(p!=0)
            printf("%s\n",str[p]);
        else
            printf("eh\n");
    }
    return 0;
}
