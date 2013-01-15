/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

const int MAXN=500000;
const int MAXM=20;
const int tk=26,tb='a';

const char *END="END";
const char *START="START";

char str[MAXN][MAXM];
int tree[MAXN*MAXM][tk+1];
int top;

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

bool isalpha(char c)
{
    if(c>='a' && c<='z')
        return true;
    return false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    char s[3010],line[3010];
    int i=1;
    init();
    while(gets(line) && strcmp(line,START));
    while(scanf("%s",str[i])==1 && strcmp(str[i],END))
    {
        scanf("%s",s);
        insert(s,i);
        i++;
    }
    while(gets(line) && strcmp(line,START));
    while(gets(line) && strcmp(line,END))
    {
        int p=0;
        int nLen=strlen(line);
        for(int i=0;i<nLen;i++)
        {
            if(isalpha(line[i]))
            {
                s[p++]=line[i];
            }
            else
            {
                if(p!=0)
                {
                    if(p>11)
                    {
                        printf("%s",s);
                    }
                    else
                    {
                        s[p]=0;
                        int ans=sear(s);
                        if(ans!=0)
                            printf("%s",str[ans]);
                        else
                            printf("%s",s);
                        p=0;
                    }
                }
                printf("%c",line[i]);
            }
        }
        puts("");
    }
    return 0;
}
