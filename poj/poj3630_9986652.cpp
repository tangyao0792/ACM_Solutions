#include<cstdio>
#include<cstring>

const int MAXN=10000;
const int MAXM=20;
const int tk=10,tb='0';

char str[MAXN][MAXM];
int tree[1<<16][tk+1];
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
    int t,n;
    scanf("%d",&t);
    while(t--)
    {
        init();
        scanf("%d",&n);
        for(int i=0;i<n;i++)
        {
            scanf("%s",str[i]);
            insert(str[i],i+1);
        }
        bool flag=false;
        for(int i=0;i<n && !flag;i++)
        {
            int nLen=strlen(str[i]);
            for(int j=1;j<nLen;j++)
            {
                char tmp[20];
                strcpy(tmp,str[i]);
                tmp[j]=0;
                if(sear(tmp)!=0)
                {
                    flag=true;
                    break;
                }
            }
        }
        if(!flag)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
