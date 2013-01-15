#include<iostream>
#include<algorithm>
#include<string>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;


bool cmp(string a, string b);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r", stdin);
#endif
    int n, i;

    while(cin >> n)
    {
        string num[60];
        if(n == 0)
        {
            break;
        }
        for(i = 0; i < n; i++)
        {
            cin >> num[i];
        }
        sort(num, num+n, cmp);
        for(i = 0; i < n; i++)
        {
            cout << num[i];
        }
        cout << endl;
    }

    return 0;
}

bool cmp(string a, string b)
{
    string c, d;
    c = a + b;
    d = b + a;
    return (c>d);
}
