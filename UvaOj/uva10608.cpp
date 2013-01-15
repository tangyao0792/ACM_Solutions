#include<iostream>
#include<cstring>
#include<algorithm>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

int c[30100];

int find(int cur);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase;
    cin >> nCase;
    while( nCase--)
    {
        memset(c, -1, sizeof(c));
        int n, m;
        cin >> n >> m;
        for(int i = 0; i < m; i++)
        {
            int x, y;
            cin >> x >> y;
            int px = find(x);
            int py = find(y);
            if( px != py)
            {
                c[px] += c[py];
                c[py] = px;
            }
        }
        int nMax = 0;
        for(int i = 1; i <= n; i++)
        {
            int t = find(i);
            if( -c[t] > nMax)
            {
                nMax = -c[t];
            }
        }
        cout << nMax << endl;
    }
}

int find(int cur)
{
    if(c[cur] >= 0)
    {
        return c[cur] = find(c[cur]);
    }
    else
    {
        return cur;
    }
}


//自己的做法
//#include<iostream>
//#include<cstring>
//#include<algorithm>
//
//#ifndef ONLINE_JUDGE
//    #include<cstdio>
//#endif
//
//using namespace std;
//
//int c[30100];
//
//int find(int cur);
//
//int main()
//{
//#ifndef ONLINE_JUDGE
//    freopen("in.txt", "r", stdin);
//#endif
//    int nCase;
//    cin >> nCase;
//    while( nCase--)
//    {
//        memset(c, -1, sizeof(c));
//        int n, m;
//        cin >> n >> m;
//        for(int i = 0; i < m; i++)
//        {
//            int x, y;
//            cin >> x >> y;
//            int px = find(x);
//            int py = find(y);
//            c[px] = py;
//        }
//        for(int i = 1; i <= n; i++)
//        {
//            find(i);
//        }
//        sort(c+1, c+n);
//        int nMax = 0;
//        int i = 1;
//        while( i <= n)
//        {
//            if(c[i] == -1)
//            {
//                i++;
//                continue;
//            }
//            int cur = 1;
//            while( i <= n)
//            {
//                i++;
//                if(c[i] != c[i-1])
//                {
//                    break;
//                }
//                cur++;
//            }
//            if( cur > nMax) nMax = cur;
//        }
//        cout << nMax << endl;
//    }
//}
//
//int find(int cur)
//{
//    if(c[cur] == -1 || c[cur] == cur)
//    {
//        return c[cur] = cur;
//    }
//    else
//    {
//        return c[cur] = find(c[cur]);
//    }
//}
