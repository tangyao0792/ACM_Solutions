#include<iostream>
//#include<stdio.h>
using namespace std;

typedef struct Tree
{
    int w;
    Tree *l, *r;
}Tree, *pTree;

int sum, flag, d;

void make_tree(pTree &p);
void preTraverse(pTree p);

int main()
{
  //  freopen("in.txt", "r", stdin);
    while(cin >> d)
    {
        char c;
        pTree p = NULL;
        sum = 0;
        flag = 0;
        cin >> c;
        if(c == '(')
        {
            make_tree(p);
        }
        if(p == NULL)
        {
            cout << "no" << endl;
            continue;
        }
        preTraverse(p);
        if(flag == 1)
        {
            cout << "yes" << endl;
        }
        else
        {
            cout << "no" << endl;
        }
    }
    return 0;
}
void preTraverse(pTree p)
{
    if(flag == 1)
    {
        return;
    }
    if(p == NULL)
    {
        return;
    }
    sum += p->w;
    if(p->l == NULL &&p->r == NULL)
    {
        if(sum == d)
        {
            flag = 1;
            return;
        }
    }
    else
    {

        preTraverse(p->l);
        preTraverse(p->r);

    }sum -= p->w;
}
void make_tree(pTree &p)
{
    char c;
    int i;
    if(cin >> i)        //输入成果说明是int
    {
        p = new Tree;
        p->w = i;
        p->l = NULL;
        p->r = NULL;
    }
    else            //输入的是)
    {
        cin.clear();
        cin >> c;
        return;
    }
    cin >> c;
    if(c == '(')
    {
        make_tree(p->l);
    }
    else
    {
        return;
    }
    cin >> c;
    if(c == '(')
    {
        make_tree(p->r);
    }
    else
    {
        return;
    }
    cin >> c;
}
