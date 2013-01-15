/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

const int MAXM=128;

struct node
{
    int count;
    node* fail;
    node* next[MAXM];
    node()
    {
        fail=NULL;
        count=0;
        for(int i=0;i<MAXM;i++)    next[i]=NULL;
    }
}*que[500*210];

const int MAXN=510;

int flag[MAXN];
int n,w;

void insert(char *s,node *root,int id)
{
    node *p=root;
    for(int i=0;s[i];i++)
    {
        int index=s[i];
        if(p->next[index]==NULL)
        {
            p->next[index]=new node;
        }
        p=p->next[index];
    }
    p->count=id;
}

void ac(node *root)
{
    int front=0,rear=0;
    que[front++]=root;
    while(front>rear)
    {
        node *p=que[rear++];
        for(int i=0;i<MAXM;i++)
        {
            if(p->next[i]!=NULL)
            {
                if(p==root)
                {
                    p->next[i]->fail=root;
                }
                else
                {
                    node* tmp=p->fail;
                    while(tmp!=NULL)
                    {
                        if(tmp->next[i]!=NULL)
                        {
                            p->next[i]->fail=tmp->next[i];
                            break;
                        }
                        tmp=tmp->fail;
                    }
                    if(tmp==NULL)
                        p->next[i]->fail=root;
                }
                que[front++]=p->next[i];
            }
        }
    }
}

void query(char *s,node *root)
{
    node *p=root;
    for(int i=0;s[i];i++)
    {
        int index=s[i];

        while(p->next[index]==NULL && p!=root)
            p=p->fail;

        p=p->next[index];

        if(p==NULL) p=root;
        node *tmp=p;

        while(tmp!=NULL)
        {
            flag[tmp->count]=1;
            tmp=tmp->fail;
        }
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d",&n)==1)
    {
        node *root=new node;
        for(int i=1;i<=n;i++)
        {
            char str[220];
            scanf("%s",str);
            insert(str,root,i);
        }
        ac(root);
        scanf("%d",&w);
        int cntw=0;
        for(int i=1;i<=w;i++)
        {
            bool has=false;
            memset(flag,0,sizeof(flag));

            char line[10100];
            scanf("%s",line);

            query(line,root);

            for(int j=1;j<=n;j++)
                if(flag[j])
                {
                    has=true;
                    break;
                }
            if(has)
            {
                cntw++;
                printf("web %d:",i);
                for(int j=1;j<=n;j++)
                    if(flag[j])
                        printf(" %d",j);
                printf("\n");
            }
        }
        printf("total: %d\n",cntw);
    }
    return 0;
}
