#include<iostream>
#include<string.h>

#include<stdio.h>

using namespace std;


void make_tree(int * fig, int len);

char input[2050];
int  step;
int main()
{
    freopen("in.txt", "r", stdin);
    int n, i,j;
    int *figure = new int[1024];
    cin >> n;
    for(i = 0; i < n; i++)
    {
        memset(figure,0,sizeof(int) * 1024);

        cin >> input;
        step = 0;


        make_tree(figure, 32);

        cin >> input;
        step = 0;
        make_tree(figure, 32);

        int sum = 0;
        for(j = 0; j < 1024; j++)
        {
            if(figure[j] == 1)
            {
                sum++;
            }
        }
        cout << "There are "<<sum <<" black pixels."<< endl;
    }
    return 0;
}

void make_tree(int *figure, int len)
{
    char c = input[step++];
    int i,j;
    if(c == 'p')
    {
        for(int i = 0; i < 4; i++)
        {
            make_tree(&figure[(i%2)*len/2+i/2*32*len/2],len/2);
        }
    }
    else if( c == 'f')
    {
        for(i = 0; i < len; i++)
        {
            for(j = 0; j < len; j++)
            {
                figure[i*32+j] = 1;
            }
        }
    }
}
//#include<iostream>
//#include<string.h>
//
//#include<stdio.h>
//
//using namespace std;
//
//typedef struct Tree
//{
//    int d;
//    Tree *c[4];
//}Tree, *pTree;
//
//void make_tree(pTree &p,int * fig, int len);
//
//char input[2050];
//int  step;
//int main()
//{
//    freopen("in.txt", "r", stdin);
//    int n, i,j;
//    int *figure = new int[1024];
//    cin >> n;
//    for(i = 0; i < n; i++)
//    {
//        memset(figure,0,sizeof(int) * 1024);
//
//        cin >> input;
//        step = 0;
//        pTree p;
//
//        make_tree(p,figure, 32);
//
//        cin >> input;
//        step = 0;
//        make_tree(p,figure, 32);
//
//        int sum = 0;
//        for(j = 0; j < 1024; j++)
//        {
//            if(figure[j] == 1)
//            {
//                sum++;
//            }
//        }
//        cout << "There are "<<sum <<" black pixels."<< endl;
//    }
//    return 0;
//}
//
//void make_tree(pTree &p,int *figure, int len)
//{
//
//    p = new Tree;
//    char c = input[step++];
//    int i,j;
//    if(c == 'p')
//    {
//        p->d = -1;
//        for(int i = 0; i < 4; i++)
//        {
//            make_tree(p->c[i],figure+(i%2)*len/2+(i/2)*len*len/2,len/2);
//        }
//    }
//    else if(c == 'e')
//    {
//        p->d = 0;
//        for( i = 0; i < 4; i++)
//        {
//            p->c[i] = NULL;
//        }
//    }
//    else if( c == 'f')
//    {
//        p->d = 1;
//        for(i = 0; i < len; i++)
//        {
//            for(j = 0; j < len; j++)
//            {
//                figure[i*32+j] = 1;
//            }
//        }
//        for(i = 0; i < 4; i++)
//        {
//            p->c[i] = NULL;
//        }
//    }
//}
