#include<iostream>
#include<sstream>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

string line;
long long nMax, nMin;

void calcMin(int l, int r);
void calcMax(int l, int r);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase;
    cin >> nCase;
    getline(cin, line);
    while( nCase--)
    {
        nMax = 1;
        nMin = 0;
        getline(cin, line);
        calcMin(0, line.size());
        calcMax(0, line.size());
        cout<<"The maximum and minimum are "<<nMax
            <<" and "
            <<nMin << "." << endl;
    }
    return 0;
}

void calcMax(int l, int r)
{
    int i;
    for(i = l; i < r; i++)
    {
        if( line[i] == '*')
        {
            calcMax(l, i);
            calcMax(i+1, r);
            return;
        }
    }
    string temp = "";
    for(i = l; i < r; i++)
    {
        temp.insert(temp.end(), line[i]);
    }
    stringstream ss(temp);
    int a, b;
    char c;
    ss >> a;
    while(ss >> c)
    {
        ss >> b;
        a = a+b;
    }
    nMax *= a;
}

void calcMin(int l, int r)
{
    int i;
    for(i = l; i < r; i++)
    {
        if( line[i] == '+')
        {
            calcMin(l, i);
            calcMin(i+1, r);
            return;
        }
    }
    string temp = "";
    for(i = l; i < r; i++)
    {
        temp.insert(temp.end(), line[i]);
    }
    stringstream ss(temp);
    int a, b;
    char c;
    ss >> a;
    while(ss >> c)
    {
        ss >> b;
        a = a*b;
    }
    nMin += a;
}
