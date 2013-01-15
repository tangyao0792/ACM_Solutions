#include<iostream>

#ifndef ONLINE_JUDGE
    #include<stdio.h>
#endif

using namespace std;

int nFlag;


int sum();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int n, i;
    cin >> n;

    for(i = 0; i < n; i++)
    {
        nFlag = 1;
        sum();
        if(i)
        {
            cout << endl;
        }
        if(nFlag == 1)
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }
    return 0;
}

int sum()
{
    int wl, dl, wr, dr;
    cin >> wl >> dl >> wr >> dr;
    if(wl == 0)
    {
        wl = sum();
    }
    if(wr == 0)
    {
        wr = sum();
    }
    if(wl * dl != wr * dr)
    {
        nFlag = 0;
    }
    return wl+wr;
}


