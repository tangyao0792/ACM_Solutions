#include<iostream>
#include<map>
#include<string>
#include<sstream>
#include<cstring>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    string st;
    map<string, string> mss;
    while(getline(cin, st))
    {
        if( st.size() == 0)
        {
            break;
        }
        stringstream ss(st);
        string a, b;
        ss >> a;
        ss >> b;
        mss.insert(pair<string, string>(b, a));
    }

    while(getline(cin, st))
    {
        map<string, string>::iterator it;
        it = mss.find(st);
        if(it == mss.end())
        {
            cout << "eh" << endl;
        }
        else
        {
            cout << it->second << endl;
        }
    }
    return 0;
}
