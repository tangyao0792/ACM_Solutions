/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

struct node
{
    int count;
    node* fail;
    node* next[26];
    node()
    {
        fail=NULL;
        count=0;
        for(int i=0;i<26;i++)    next[i]=NULL;
    }
}*que[1000000];

int n;

void insert(char *s,node *root)
{
    node *p=root;
    for(int i=0;s[i];i++)
    {
        int index=s[i]-'a';
        if(p->next[index]==NULL)
        {
            p->next[index]=new node;
        }
        p=p->next[index];
    }
    p->count++;
}

void AC(node *root)
{
    int front=0,rear=0;
    root->fail=NULL;
    que[front++]=root;
    while(rear<front)
    {
        node *tmp=que[rear++];
        node *p=NULL;
        for(int i=0;i<26;i++)
        {
            if(tmp->next[i]!=NULL)
            {
                if(tmp==root)
                    tmp->next[i]->fail=root;
                else
                {
                    p=tmp->fail;
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

int query(char *str,node *root)
{
    int ans=0;
    node *p=root;
    for(int i=0;str[i];i++)
    {
        int index=str[i]-'a';
        while(p->next[index]==NULL && p!=root)
        {
            p=p->fail;
        }
        p=p->next[index];
        if(p==NULL) p=root;
        node *tmp=p;
        while(tmp!=root && tmp->count!=-1)
        {
            ans+=tmp->count;
            tmp->count=-1;
            tmp=tmp->fail;
        }
    }
    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase;
    scanf("%d",&nCase);
    while(nCase--)
    {
        scanf("%d",&n);
        node *root=new node;

        for(int i=0;i<n;i++)
        {
            char str[100];
            scanf("%s",str);
            insert(str,root);
        }
        AC(root);
        char line[1000100];
        scanf("%s",line);
        printf("%d\n",query(line,root));
    }
    return 0;
}
