#include<iostream>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    string a, b;
    int lenA, lenB, i, j;
    while (cin >> a >> b)
    {
        lenA = a.size();
        lenB = b.size();
        j = 0;
        for(i = 0; i < lenA; i++)
        {
            for(; j < lenB; j++)
            {
                if( a[i] == b[j])
                {
                    break;
                }
            }
            if(j == lenB)
            {
                cout << "No" << endl;
                break;
            }
        }
        if(i == lenA)
        {
            cout << "Yes" << endl;
        }

    }
    return 0;
}
