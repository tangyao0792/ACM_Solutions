#include<iostream>
#include<cstring>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

char str[1100];
int vis[1100][1100];
int d[1100][1100];
int nLen;

int dp(int x, int y);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase, iCase;
    cin >> nCase;
    for( iCase = 1; iCase <= nCase; iCase++)
    {
        memset( str, 0, sizeof(str));
        memset( vis, 0, sizeof(vis));
        memset (d, 0, sizeof(d));
        cin >> str;
        nLen = strlen( str);
        cout << "Case " << iCase << ": " << dp( 0, nLen-1) << endl;
    }
    return 0;
}

int dp(int x, int y)
{
    if( vis[x][y])
    {
        return d[x][y];
    }
    vis[x][y] = 1;
    if(x == y)
    {
        return 0;
    }
    if( x == y-1)
    {
        if( str[x] == str[y])
        {
            d[x][y] = 0;
            return 0;
        }
        else
        {
            d[x][y] = 1;
            return 1;
        }
    }
    if( str[x] == str[y])
    {
        d[x][y] = dp(x+1, y-1);
        return d[x][y];
    }
    int nMin = dp(x+1, y)+1;
    int temp = dp(x, y-1)+1;
    nMin = min(nMin, temp);
    temp = dp(x+1, y-1)+1;
    nMin = min(nMin, temp);
    d[x][y] = nMin;
    return nMin;
}
