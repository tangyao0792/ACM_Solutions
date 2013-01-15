#include<iostream>
#include<stdio.h>

using namespace std;

typedef struct Tree
{
    int d;
    Tree *l, *r;
}Tree, *pTree;

int leaves[1000];

void createTree(pTree &p);
void preTraverse(pTree p, int cur);

int main()
{
    freopen("in.txt", "r", stdin);

    int d;
    int nCount = 0;
    int i;
    while(cin >> d)
    {
        if(d == -1)
        {
            break;
        }
        for(i = 0; i < 1000; i++)
        {
            leaves[i] = 0;
        }
        nCount++;
        cout << "Case " << nCount << ":" << endl;
        pTree p = new Tree;
        p->d = d;
        createTree(p->l);
        createTree(p->r);

        preTraverse(p, 500);
        int nFlag = 0;
        for(i = 0; i < 1000; i++)
        {

            if(leaves[i] != 0)
            {
                if(nFlag != 0)
                {
                    cout << " ";
                }
            nFlag = 1;
                cout << leaves[i];
            }
        }
        cout << endl << endl;
    }
    return 0;
}
void preTraverse(pTree p, int cur)
{
    if(p == NULL)
    {
        return;
    }
    //cout << p->d << " ";
    leaves[cur] += p->d;
    preTraverse(p->l, cur - 1);
    preTraverse(p->r, cur +1);
}
void createTree(pTree &p)
{
    int d;
    p = new Tree;
    cin >> d;
    if(d == -1)
    {
        p = NULL;
    }
    else
    {
        p->d = d;
        createTree(p->l);
        createTree(p->r);
    }
}
