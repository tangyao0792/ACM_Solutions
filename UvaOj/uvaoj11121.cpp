#include<iostream>
#include<stack>
#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase, iCase;
    cin >> nCase;
    long long x;
    stack<int> s;
    for(iCase = 1; iCase <= nCase; iCase++)
    {
        cin >> x;
        cout << "Case #"<<iCase<<": ";
        if (x == 0 )
        {
            cout << 0;
        }
        else
        {
            while(x != 0)
            {
                if( x %(-2) != 0)
                {
                    s.push(1);
                }
                else
                {
                    s.push(0);
                }
                if( x %(-2) == -1)
                {
                    x = x/(-2) +1;
                }
                else
                {
                    x = x/(-2);
                }
            }
            while( !s.empty())
            {
                cout << s.top();
                s.pop();
            }
        }
        cout << endl;
    }
    return 0;
}
