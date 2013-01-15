#include<iostream>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

int a[60], p[6];
int s;

void swap(int &a, int &b);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase, n, i, j;
    cin >> nCase;
    while( nCase--)
    {
        cin >> n;
        for(i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        s = 0;
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < n-i-1; j++)
            {
                if(a[j] > a[j+1])
                {
                    swap(a[j], a[j+1]);
                }
            }
        }
        cout << "Optimal train swapping takes " << s
        <<" swaps." << endl;
    }
    return 0;
}

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
    s++;
}
