#include<iostream>
#include<cstring>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

int vis[5000];
int d[5000];

int dp(int x);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int i;
    for(i = 0; i < 1<<12; i++)
    {
        d[i+1] = dp(i+1);
    }
    int nCase;
    cin >> nCase;
    string line;
    getline(cin, line);

    while( nCase--)
    {
        int x = 0;
        getline(cin, line);
        for(i = 11; i >= 0; i--)
        {
            if( line[i] == 'o')
            {
                x += 1<<(11-i);
            }
        }

        cout << d[x] << endl;
    }
    return 0;
}

int dp( int x)
{
    if( vis[x])
    {
        return d[x];
    }
    int i, nMin;
    nMin = 15;
    bool flag = true;
    for(i = 0; i < 12; i++)
    {
        if( i < 10)
        {
            if((x & 1<<i) && (x & 1<<(i+1)) && !(x & 1<<(i+2)))
            {
                nMin = min(nMin, dp(x-(1<<(i))- (1<<(i+1))+ (1<<(i+2))));
                flag = false;
            }
            if( !(x&1<<i) && (x&1<<(i+1)) && (x& 1<<(i+2)))
            {
                nMin = min(nMin, dp(x+(1<<i)-(1<<(i+1))-(1<<(i+2))));
                flag = false;
            }
        }
    }
    if( flag)
    {
        nMin = 0;
        for(i = 0; i < 12; i++)
        {
            if(x & 1<<i)
            {
                nMin++;
            }
        }
    }
    d[x] = nMin;
    vis[x] = 1;
    return nMin;
}
