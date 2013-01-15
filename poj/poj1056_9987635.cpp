#include<cstdio>
#include<cstring>

const int MAXN=20;
const int MAXM=20;
const int tk=2,tb='0';

char str[MAXN*MAXM][MAXM];
int tree[MAXN*MAXM][tk+1];
int num[MAXN*MAXM];
int top,cnt;

void init()
{
    top=1;
    memset(tree[0],0,sizeof(tree[0]));
    num[0]=0;
}

void insert(char *s)
{
    int rt,nxt;
    for(rt=0;*s;rt=nxt,s++)
    {
        nxt=tree[rt][*s-tb];
        if(rt)
            num[rt]++;
        if(nxt==0)
        {
            tree[rt][*s-tb]=nxt=top;
            memset(tree[top],0,sizeof(tree[top]));
            num[top]=0;
            top++;
        }
    }
    if(rt)  num[rt]++;
    tree[rt][tk]=1;
}

bool sear(char *s)
{
    for(int rt=0;(rt=tree[rt][*s-tb]);)
    {
        if(*(++s)==0)
        {
            if(num[rt]>1)   return false;
            else    return true;
        }
    }
    return false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase=0;
    while(gets(str[1]))
    {
        init();
        nCase++;
        cnt=1;
        insert(str[cnt]);
        cnt++;
        while(gets(str[cnt]) && str[cnt][0]!='9')
        {
            insert(str[cnt]);
            cnt++;
        }
        bool flag=true;
        for(int i=1;i<cnt && flag; i++)
        {
            flag=sear(str[i]);
        }
        if(flag)
            printf("Set %d is immediately decodable\n",nCase);
        else
            printf("Set %d is not immediately decodable\n",nCase);
    }
    return 0;
}
