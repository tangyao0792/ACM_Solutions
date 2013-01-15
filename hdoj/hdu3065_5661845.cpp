/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

const int MAXN=1100;
const int MAXM=60;

char word[MAXN][MAXM];
char cnt[MAXN];

int n;

struct node
{
    int count;
    node* fail;
    node* next[26];
    node()
    {
        fail=NULL;
        count=0;
        memset(next,0,sizeof(next));
    }
}*que[10000000];

void insert(char *str,int num,node *root)
{
    node *p=root;
    for(int i=0;str[i];i++)
    {
        int index=str[i]-'A';
        if(p->next[index]==NULL)
        {
            p->next[index]=new node;
        }
        p=p->next[index];
    }
    p->count=num;
}

void ac(node *root)
{
    int front=0,rear=0;
    que[front++]=root;
    while(front>rear)
    {
        node* tmp=que[rear++];
        for(int i=0;i<26;i++)
        {
            if(tmp->next[i]!=NULL)
            {
                if(tmp==root)
                    tmp->next[i]->fail=root;
                else
                {
                    node *p=tmp->fail;
                    while(p!=NULL)
                    {
                        if(p->next[i]!=NULL)
                        {
                            tmp->next[i]->fail=p->next[i];
                            break;
                        }
                        p=p->fail;
                    }
                    if(p==NULL)
                        tmp->next[i]->fail=root;
                }
                que[front++]=tmp->next[i];
            }
        }
    }
}

void query(char *str,node* root)
{
    node* p=root;
    for(int i=0;str[i];i++)
    {
        int index;
        if(str[i]>='A' && str[i]<='Z')
            index=str[i]-'A';
        else
        {
            p=root;
            continue;
        }
        while(p->next[index]==NULL && p!=root)
        {
            p=p->fail;
        }
        p=p->next[index];
        if(p==NULL) p=root;
        node *tmp=p;
        while(tmp!=root)
        {
            cnt[tmp->count]++;
            tmp=tmp->fail;
        }
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r", stdin);
#endif
    while(scanf("%d", &n)==1)
    {
        node *root=new node;
        memset(cnt,0,sizeof(cnt));
        for(int i=1;i<=n;i++)
        {
            scanf("%s",word[i]);
            insert(word[i],i,root);
        }
        ac(root);
        char line[2000100];

        scanf("%s",line);
        query(line,root);
        for(int i=1;i<=n;i++)
        {
            if(cnt[i])
                printf("%s: %d\n",word[i],cnt[i]);
        }
    }
    return 0;
}
