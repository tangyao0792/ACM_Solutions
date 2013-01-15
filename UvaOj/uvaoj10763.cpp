#include<iostream>
#include<cstring>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

#define N 10000
int loc[N];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase, i, original, target;
    while(cin >> nCase)
    {
        if(nCase == 0)
        {
            break;
        }
        memset(loc, 0, sizeof(int) * N);
        for(i = 0; i < nCase; i++)
        {
            cin >> original >> target;
            loc[original]--;
            loc[target]++;
        }
        for(i = 0; i < N; i++)
        {
            if(loc[i] != 0)
            {
                cout << "NO" << endl;
                break;
            }
        }
        if(i == N)
        {
            cout << "YES" << endl;
        }
    }
    return 0;
}
