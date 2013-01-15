#include<iostream>
#include<cmath>
#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    unsigned long n, t;
    while(cin >> n)
    {
        if(n == 0)
        {
            break;
        }
        t = (unsigned long) sqrt(n);
        if(t * t == n)
        {
            cout << "yes" << endl;
        }
        else
        {
            cout << "no" << endl;
        }
    }
    return 0;
}
