#include<iostream>
#include<sstream>
#include<cstring>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

int n;
int order[25];
int ans[25];
int arr[25];
int in[25];

int d[25];
int vis[25];

int dp(int cur);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    cin >> n;
    int i, j;
    for(i = 1; i <= n; i++)
    {
        cin >> ans[i];
    }
    string line;
    getline(cin, line);
    while( getline(cin, line))
    {
        memset(d, 0, sizeof(d));
        memset(vis, 0, sizeof(vis));

        stringstream ss(line);
        for(i = 1; i <= n; i++)
        {
            ss >> j;
            in[j] = i;
        }
        for(i = 1; i <= n; i++)
        {
            arr[i-1] = ans[in[i]];
        }
        for(i = n-1; i >= 0; i--)
        {
            d[i] = dp(i);
        }
        int nMax = d[0];
        for(i = 0; i < n; i++)
        {
            if( d[i] > nMax)
            {
                nMax = d[i];
            }
        }
        cout << nMax << endl;
    }
    return 0;
}

int dp(int cur)
{
    if(vis[cur])
    {
        return d[cur];
    }
    int i, nMax;
    nMax = 1;
    for(i = cur+1; i < n; i++)
    {
        if( arr[i] > arr[cur])
        {
            nMax = max(nMax, d[i]+1);
        }
    }
    vis[cur] = 1;
    d[cur] = nMax;
    return nMax;
}
