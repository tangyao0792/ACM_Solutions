/*
Õÿ∆À≈≈–Ú
*/



#include<iostream>
#include<cstring>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

int n, m;
int g[110][110];
int d[110];         //»Î∂»
int vis[110];
int pre[110];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while(cin >> n >> m)
    {
        if( n == 0 && m == 0)
        {
            break;
        }
        memset( g, 0, sizeof(int ) * 110 * 110);
        memset( vis, 0, sizeof(int) * 110);
        memset( d, 0, sizeof(int ) * 110);
        int i, j, k, x, y;
        for(i = 0; i < m; i++)
        {
            cin >> x >> y;
            g[x][y] = 1;
            d[y]++;
        }
        j = 0;
        while(j < n)
        for(i = 1; i <= n; i++)
        {
            if(d[i] == 0 && !vis[i])
            {
                pre[j++] = i;
                vis[i] = 1;
                for(k = 1; k <= n; k++)
                {
                    if( g[i][k] == 1)
                    {
                        g[i][k] = 0;
                        d[k]--;
                    }
                }
            }
        }
        for(i = 0; i < n; i++)
        {
            cout << pre[i] << " ";
        }
        cout << endl;
    }
    return 0;
}

//±©¡¶

//#include<iostream>
//#include<cstring>
//
//#ifndef ONLINE_JUDGE
//    #include<cstdio>
//#endif
//
//using namespace std;
//
//int n, m;
//int g[110][110];
//int vis[110];
//int pre[110];
//int nFlag;
//
//void dfs(int cur, int i);
//
//int main()
//{
//#ifndef ONLINE_JUDGE
//    freopen("in.txt", "r", stdin);
//#endif
//    while(cin >> n >> m)
//    {
//        if(n == 0 && m == 0)
//        {
//            break;
//        }
//        memset( g, 0, sizeof(int) * 110 * 110);
//        memset( vis, 0, sizeof(int) * 110);
//        int i, j, x, y;
//        for(i = 0; i < m; i++)
//        {
//            cin >> x >> y;
//            g[x][y] = 1;
//        }
//
//        nFlag = 0;
//        for(i = 1; i <= n && !nFlag; i++)
//        {
//            for(j = 1; j <= n; j++)
//            {
//                if( g[i][j] && vis[j])
//                {
//                    break;
//                }
//            }
//            if(j == n+1)
//            {
//                dfs(0, i);
//            }
//        }
//        if( nFlag)
//        {
//            for(i = 0; i < n; i++)
//            {
//                cout << pre[i] << " ";
//            }
//        }
//        cout << endl;
//    }
//    return 0;
//}
//
//void dfs(int cur, int i)
//{
//    pre[cur] = i;
//    if( cur == n-1)
//    {
//        nFlag = 1;
//        return;
//    }
//    vis[i] = 1;
//
//    int j, k;
//    for(j = 1; j <= n; j++)
//    {
//        if( !vis[j])
//        {
//            for(k = 1; k <= n; k++)
//            {
//                if( g[j][k] && vis[k])
//                {
//                    break;
//                }
//            }
//            if( k == n+1)
//            {
//                dfs(cur+1, j);
//                if( nFlag)return;
//            }
//        }
//    }
//    vis[i] = 0;
//}
