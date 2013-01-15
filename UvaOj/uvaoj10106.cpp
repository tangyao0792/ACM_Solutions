#include<iostream>
#include<cstring>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

int x[260], y[260], z[520];
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    string a, b;
    int i, j, nLenA, nLenB;
    int  g;
    while((getline(cin, a)) && (getline(cin, b)))
    {
        memset(x, 0, sizeof(int) * 260);
        memset(y, 0, sizeof(int) * 260);
        memset(z, 0, sizeof(int) * 520);

        nLenA = a.size();
        nLenB = b.size();
        for(i = 259; i > 259 - nLenA; i--)
        {
            x[i] = a[nLenA-260+i] - '0';
        }
        for(i = 259; i > 259 - nLenB; i--)
        {
            y[i] = b[nLenB-260+i] - '0';
        }

        for(i = 259; i > -1; i--)
        {
            g = 0;
            for(j = 259; j > -1; j--)
            {
                z[ i + j] += y[i] * x[j] + g;
                g = z[i + j] / 10;
                z[i+j] %= 10;
            }
        }
        i = 0;
        while(z[i] == 0 && i < 519)
        {
            i++;
        }
        if(i == 519)
        {
            cout << 0;
        }
        else
        {
            for(; i < 519; i++)
            {
                cout << z[i];
            }
        }
        cout << endl;
    }
    return 0;
}
