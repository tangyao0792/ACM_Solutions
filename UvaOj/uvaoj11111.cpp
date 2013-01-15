#include<iostream>
#include<stack>
#include<string>
#include<sstream>

#ifndef ONLINE_JUDGE
    #include<stdio.h>
#endif

using namespace std;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    stack<int> s;       //doll的大小
    stack<int> v;       //剩余的空间
    string st;
    int d;
    int nFlag;
    while(getline(cin, st))
    {
        nFlag = 1;
        stringstream sst(st);
        while( !s.empty())
        {
            s.pop();
        }
        while( !v.empty())
        {
            v.pop();
        }
        v.push(20000000);
        while(sst >> d)
        {
            if(d < 0)
            {
                v.push(-d);
                s.push(d);
            }
            else
            {
                if( s.empty() || v.empty())
                {
                    nFlag = 0;
                    break;
                }
                if(s.top() + d != 0)
                {
                    nFlag = 0;
                    break;
                }

                s.pop();
                v.pop();

                if(v.empty())
                {
                    nFlag = 0;
                    break;
                }
                int temp = v.top();

                v.pop();
                temp = temp - d;
                v.push(temp);

                if( v.top() < 1)
                {
                    nFlag = 0;
                    break;
                }

            }
        }
        if(!s.empty())
        {
            nFlag = 0;
        }
        if(nFlag == 1)
        {
            cout << ":-) Matrioshka!" << endl;
        }
        else
        {
            cout << ":-( Try again." << endl;
        }
    }
    return 0;
}
