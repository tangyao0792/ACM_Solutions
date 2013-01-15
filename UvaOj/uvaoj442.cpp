#include<iostream>
#include<stack>
#include<string>
#include<sstream>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

typedef struct
{
    int r, c;
}Matrix;

Matrix m[26];

void solve(string st);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase, i;
    char c;
    cin >> nCase;
    for(i = 0; i < nCase; i++)
    {
        cin >> c;
        cin >> m[c-'A'].r >> m[c-'A'].c;
    }
    string st;
    getline(cin, st);       //去最后一个矩阵的回车
    while(getline(cin, st))
    {
        solve( st);
    }
    return 0;
}

void solve(string st)
{
    stack<char> sc;
    stack<Matrix> sm;
    stringstream ss(st);
    char ch;
    Matrix a, b, c;
    int sum = 0;
    while( ss >> ch)
    {
        if( ch == ')')
        {
            a = sm.top();
            sm.pop();
            b = sm.top();
            sm.pop();

            if(b.c != a.r)
            {
                cout << "error" << endl;
                return;
            }

            sum += b.r * b.c * a.c;
            c.r = b.r;
            c.c = a.c;

            sm.push(c);

            sc.pop();       //去掉与（对应的）
        }
        else if( ch == '(')
        {
            sc.push(ch);
        }
        else
        {
            a = m[ch-'A'];
            sm.push(a);
        }
    }
    cout << sum << endl;
}
