#include<iostream>
#include<sstream>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    string line;
    while(getline(cin, line))
    {
        stringstream ss(line);
        int a, b, c;
        ss >> a >> b >> c;
        int n = 1;
        int t = b * c;
        while( t != b)
        {
            t = (t/a) + (t%a)*c;
            n++;
        }
        cout << n << endl;

    }
    return 0;
}
