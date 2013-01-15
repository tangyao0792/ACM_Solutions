#include<iostream>
#include<string.h>

using namespace std;

int main()
{
    int t, n, p;
    int i, j, k, temp;
    int sum;
    cin >> t;
    for(i = 0;i < t; i++)
    {
        cin >> n;
        int *day = new int[n+1];
        memset(day,0,(n+1) * sizeof(int));

        cin >> p;
        for(j = 0; j < p; j++)
        {
            cin >> temp;
            for(k = 1; k < n+1; k++)
            {
                if(k % 7 == 6 || k % 7 == 0)
                {
                    continue;
                }
                if(k % temp == 0)
                {
                    day[k] = 1;
                }
            }
        }
        sum = 0;
        for(k = 1; k < n+1; k++)
        {
            if(day[k] == 1)
            {
                sum++;
            }
        }
        cout << sum << endl;
        delete []day;
    }
    return 0;
}
