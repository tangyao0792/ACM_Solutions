#include<iostream>
#include<queue>
#include<stack>
#include<cstring>
#include<ctype.h>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

typedef struct Tree
{
    char c;
    Tree *l, *r;
}Tree, *pTree;

char exp[10010];
int cur;
queue<pTree> q;
void create_tree(pTree &p);
void bfs(pTree p);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase;
    int nLen;
    pTree p;
    cin >> nCase;

    while(nCase--)
    {
        cin >> exp;
        nLen = strlen(exp);
        cur = nLen-1;
        create_tree(p);
        while( !q.empty())
        {
            q.pop();
        }
        bfs(p);
    }
    return 0;
}

void bfs(pTree p)
{
    pTree temp;
    temp = p;
    q.push(temp);
    stack<char> s;
    while( !q.empty())
    {
        temp = q.front();
        q.pop();
        if(temp == NULL)
        {
            continue;
        }
        s.push(temp->c);
        q.push(temp->r);
        q.push(temp->l);
    }
    while( !s.empty())
    {
        cout << s.top();
        s.pop();
    }
    cout << endl;
}

void create_tree(pTree &p)
{
    if(cur < 0)
    {
        return;
    }
    p = new Tree;
    p->l = NULL;
    p->r = NULL;
    char c = exp[cur--];
    p->c = c;
    if(isupper(c) != 0)
    {
        create_tree(p->l);
        create_tree(p->r);
    }
}
