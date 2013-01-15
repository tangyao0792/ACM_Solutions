/*
使用vis判重比直接判断是否重复效率高
函数的调用也占用了很多的时间
*/

#include<iostream>
#include<cstring>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

int num[5];
int opn[5];
int temp[5];
int vis[5];
int opr[4];
int nFlag;

void dfsN(int cur);     //数
void dfsO(int cur);     //运算
int calculate(int a, int b, int opr);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while(cin >> num[0] >> num[1] >> num[2] >> num[3] >> num[4])
    {
        if(num[0] == 0 &&
           num[1] == 0 &&
           num[2] == 0 &&
           num[3] == 0 &&
           num[4] == 0)
        {
            break;
        }
        nFlag = 0;
        memset(vis, 0, sizeof(int)*5);
        dfsN(0);
        if(nFlag == 0)
        {
            cout << "Impossible" << endl;
        }
        else
        {
            cout << "Possible" << endl;
        }
    }
    return 0;
}

int calculate(int a, int b, int c)
{
    if(c == 1)
    {
        return a+b;
    }
    else if(c == 2)
    {
        return a-b;
    }
    else
    {
        return a*b;
    }
}

void dfsO(int cur)
{
    int i;
    if(cur == 4)
    {
        for(i = 0; i < 5; i++)
        {
            temp[i] = opn[i];
        }
        for(i = 0; i < 4; i++)
        {
            temp[i+1] = calculate(temp[i],temp[i+1],opr[i]);
        }
        if(temp[4] == 23)
        {
            nFlag = 1;
        }
        return;
    }
    for(i = 1; i <= 3 ; i++)
    {
        opr[cur] = i;
        dfsO(cur+1);
    }
}

void dfsN(int cur)
{
    if(cur == 5)
    {
        dfsO(0);
        return;
    }
    int i;
    for(i = 0; i < 5; i++)
    {
        if(vis[i] == 0)
        {
            vis[i] = 1;
            opn[cur] = num[i];
            dfsN(cur+1);
            vis[i] = 0;
        }
        if( nFlag == 1)
        {
            return;
        }
    }
}

//#include<iostream>
//#include<cstring>
//
//#ifndef ONLINE_JUDGE
//    #include<cstdio>
//#endif
//
//using namespace std;
//
//int num[5];
//int vis[5];
//int opr[4];
//int nFlag;
//
//void dfsN(int cur, int tot);
//int main()
//{
//#ifndef ONLINE_JUDGE
//    freopen("in.txt", "r", stdin);
//#endif
//    while(cin >> num[0] >> num[1] >> num[2] >> num[3] >> num[4])
//    {
//        if(num[0] == 0 &&
//           num[1] == 0 &&
//           num[2] == 0 &&
//           num[3] == 0 &&
//           num[4] == 0)
//        {
//            break;
//        }
//        nFlag = 0;
//        memset(vis, 0, sizeof(int) * 5);
//        int i;
//        for(i = 0; i < 5; i++)
//        {
//            if(vis[i] == 0)
//            {
//                vis[i] = 1;
//                dfsN(1, num[i]);
//                vis[i] = 0;
//            }
//        }
//        if(nFlag == 0)
//        {
//            cout << "Impossible" << endl;
//        }
//        else
//        {
//            cout << "Possible" << endl;
//        }
//    }
//    return 0;
//}
//
//void dfsN(int cur, int tot)
//{
//    if( nFlag == 1)
//    {
//        return;
//    }
//    if(cur == 5)
//    {
//        if(tot == 23)
//        {
//            nFlag = 1;
//        }
//        return;
//    }
//    int i;
//    for(i = 0; i < 5; i++)
//    {
//        if( vis[i] == 0)
//        {
//            vis[i] = 1;
//            dfsN(cur+1, tot+num[i]);
//            dfsN(cur+1, tot-num[i]);
//            dfsN(cur+1, tot*num[i]);
//            vis[i] = 0;
//        }
//    }
//}
