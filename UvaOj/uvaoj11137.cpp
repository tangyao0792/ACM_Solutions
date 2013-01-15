#include<iostream>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

long long dp[10010];
int a[22];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int i, j;
    for( i = 1; i < 22; i++)
    {
        a[i] = i*i*i;
    }
    dp[0] = 1;
    for(i = 1; i < 22; i++)
    {
        for(j = 1; j < 10001; j++)
        {
            if(j >= a[i])
            {
                dp[j] += dp[j-a[i]];
            }
        }
    }
    int n;
    while(cin >> n)
    {
        cout << dp[n] << endl;
    }
    return 0;
}
