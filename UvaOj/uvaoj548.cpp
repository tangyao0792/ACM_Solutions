
#include<iostream>
#include<string>
#include<sstream>

#include<stdio.h>

using namespace std;

int num[20010];
int step;
int nLeaf;
int nMin;
int nSum;
typedef struct Tree
{
    int w;
    Tree *l, *r;
}Tree, *pTree;

void scan_tree(pTree &p, int f1, int l1);
void preTraverse(pTree p);

int main()
{
    freopen("in.txt", "r", stdin);
    string si, sp;
    while(getline(cin, si))
    {
        getline(cin, sp);
        stringstream ssi(si);
        stringstream ssp(sp);

        int length = 0;
        while(ssi >> num[length])length++;    //mid+1是后续遍历的第一个数
        while(ssp >> num[length])length++;

        int mid = length / 2 -1;        //mid是中序遍历的最后一个
        pTree p;
        step =length - 1;

        scan_tree(p, 0, mid);

        nMin = 10000 * 10000;
        nSum = 0;
        preTraverse(p);
        cout << nLeaf << endl;
    }

    return 0;
}
void preTraverse(pTree p)
{
    if(p == NULL)
    {
        return;
    }

    nSum += p->w;
    if(p->l == NULL && p->r == NULL)
    {
        if(nMin > nSum)
        {
            nMin = nSum;
            nLeaf = p->w;
        }
        nSum -= p->w;
        return;
    }
    preTraverse(p->l);
    preTraverse(p->r);
    nSum -= p->w;
}
void scan_tree(pTree &p, int f1, int l1)
{

    int i;
    for(i = f1; i < l1 + 1; i++)
    {
        if(num[step] == num[i])
        {
            p = new Tree;
            p->w = num[step];
            step--;
            scan_tree(p->r, i+1, l1);
            scan_tree(p->l, f1, i-1);
            return ;
        }
    }
    p = NULL;
}

//题意弄错的代码。。

//#include<iostream>
//#include<stack>
//#include<sstream>
//#include<string>
//
//#include<stdio.h>
//
//using namespace std;
//
//typedef struct State
//{
//    int first, last;
//}State;
//
//int num[200020];
//int step;
//int main()
//{
//    stack<State> ss;
//
//   freopen("in.txt", "r", stdin);
//
//    string si,sp;
//    while(getline(cin, si))
//    {
//        getline(cin, sp);
//        stringstream strmi(si);
//        int length = 0;
//        while(strmi >> num[length])length++;
//
//        stringstream strmp(sp);
//        while(strmp >> num[length])length++;
//
//        int mid = length/2-1;
//        step = length - 1;
//
//        int f = 0;
//        int l = mid;
//        State *s = new State;
//        s->first = f;
//        s->last = l;
//        ss.push(*s);
//        int min = 100010;
//        while( !ss.empty())
//        {
//            s = &ss.top();
//            ss.pop();
//            f = s->first;
//            l = s->last;
//
//            if(l == f)
//            {
//                if(num[l] < min)
//                {
//                    min = num[l];
//                }
//                step--;
//                continue;
//            }
//
//            for(int i = f; i < l+1; i++)
//            {
//                if(num[step] == num[i])
//                {
//                    step--;
//
//                    s = new State;
//                    s->first = f;
//                    s->last = i-1;
//                    ss.push(*s);
//
//                    s = new State;
//                    s->first = i+1;
//                    s->last = l;
//                    ss.push(*s);
//
//                    break;
//                }
//            }
//        }
//        cout << min << endl;
//    }
//
//    return 0;
//}
//
//

