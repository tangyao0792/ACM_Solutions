#include<iostream>
#include<algorithm>
#include<cmath>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

int a[1010];
int s[1010*1010];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int i, j, k, x, l, r, n, m, mid;
    int nCount = 0;
    while( cin >> n)
    {
        if( n == 0)
        {
            break;
        }
        nCount++;
        cout << "Case " << nCount << ":" << endl;
        for(i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        k = 0;
        for(i = 0; i < n ; i++)
        {
            for(j = i+1; j < n; j++)
            {
                s[k++] = a[i] + a[j];
            }
        }
        sort(s, s+k);
        cin >> m;
        for(i = 0; i < m; i++)
        {
            cin >> x;
            l = 0;
            r = k-2;
            cout << "Closest sum to " << x<<" is ";
            if( x < s[0])
            {
                cout << s[0] << "." <<endl;
            }
            else if( x > s[k-1])
            {
                cout << s[k-1] << "." << endl;
            }
            else
            {
                while( true)
                {
                    mid = (l+r)/2;
                    if( s[mid] > x)
                    {
                        r = mid-1;
                    }
                    else if( s[mid+1] < x)
                    {
                        l = mid+1;
                    }
                    else
                    {
                        break;
                    }
                }
                if( fabs(s[mid]-x) < fabs(s[mid+1]-x))
                {
                    cout << s[mid] << "." << endl;
                }
                else
                {
                    cout << s[mid+1] << "." << endl;
                }
            }
        }
    }
    return 0;
}
