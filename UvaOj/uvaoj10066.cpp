#include<iostream>
#include<cstring>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

int n1, n2;
int t1[110], t2[110];
int d[110][110];
int vis[110][110];

int dp(int l1, int l2);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCount = 0;
    while( cin >> n1 >> n2)
    {
        if(n1 == 0 && n2 == 0)
        {
            break;
        }
        memset( d, 0, sizeof(d));
        memset( vis, 0, sizeof(vis));
        nCount++;
        int i;
        for(i = 0; i < n1; i++)
        {
            cin >> t1[i];
        }
        for(i = 0; i < n2; i++)
        {
            cin >> t2[i];
        }
        cout << "Twin Towers #"<<nCount<<endl
            << "Number of Tiles : " << dp(n1-1,n2-1)<<endl<<endl;
    }
    return 0;
}

int dp(int l1, int l2)
{
    if(l1 == -1 || l2 == -1)
    {
        return 0;
    }
    if( vis[l1][l2])
    {
        return d[l1][l2];
    }
    vis[l1][l2] = 1;

    if( t1[l1] == t2[l2])
    {
        d[l1][l2] = dp(l1-1, l2-1)+1;
    }
    else
    {
        int temp1 = dp(l1-1, l2);
        int temp2 = dp(l1, l2-1);
        d[l1][l2] = max(temp1, temp2);
    }
    return d[l1][l2];
}
