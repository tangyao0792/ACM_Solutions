#include<cstdio>
#include<cstring>
#include<iostream>
#include<set>

using namespace std;

const int MAXN=3100;
const int MAXM=40;
const int tk=26,tb='a';

char str[MAXN][MAXM];
int tree[MAXN*MAXM][tk+1];
int ss[MAXN*MAXM];

int cnt,top;

void init()
{
    top=1;
    ss[0]=0;
    memset(tree[0],0,sizeof(tree[0]));
}

int sear(char *s, int rank)
{
    for(int rt=0;(rt=tree[rt][*s-tb]);)
    {
        if(*(++s)==0)
        {
            if(ss[rt]>1)    return tree[rt][tk];
            break;
        }
    }
    return -1;
}

void insert(char *s,int rank)
{
    int rt,nxt;
    for(rt=0;*s;rt=nxt,s++)
    {
        nxt=tree[rt][*s-tb];
        if(rt!=0)
        {
            ss[rt]++;
            tree[rt][tk]=rank;
        }

        if(nxt==0)
        {
            tree[rt][*s-tb]=nxt=top;
            memset(tree[top],0,sizeof(tree[top]));
            ss[top]=0;
            top++;
        }
    }
    if(rt!=0)
    {
        ss[rt]++;
        tree[rt][tk]=rank;
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    cnt=1;
    init();
    while(scanf("%s",str[cnt])==1)
    {
        insert(str[cnt],cnt);
        cnt++;
    }

    for(int i=1;i<cnt;i++)
    {
        int nLen=strlen(str[i]);
        char tmp[MAXM];

        printf("%s ",str[i]);
        bool flag=false;

        for(int j=1;j<nLen+1;j++)
        {
            strcpy(tmp,str[i]);
            tmp[j]=0;
            if(sear(tmp,i)==-1)
            {
                flag=true;
                printf("%s",tmp);
                break;
            }
        }
        if(!flag)
        {
           printf("%s",str[i]);
        }
        printf("\n");
    }
    return 0;
}
