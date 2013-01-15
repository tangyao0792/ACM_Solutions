#include<iostream>
#include<cmath>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

int sales[100100];
int n;
long long sum;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while(cin >> n)
    {
        if(n == 0)
        {
            break;
        }
        int i;
        for(i = 0; i < n; i++)
        {
            cin >> sales[i];
        }
        sum = 0;
        for(i = 0; i < n-1; i++)
        {
            sales[i+1] += sales[i];
            sum += abs((double)sales[i]);
            sales[i] = 0;
        }
        cout << sum << endl;
    }
    return 0;
}
