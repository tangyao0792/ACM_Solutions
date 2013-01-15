#include<iostream>

#ifndef ONLINE_JUDGE
#include<stdio.h>
#endif

using namespace std;

int x[105];
int y[105];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int n;
    int i, j, k;
    int nCountA, nCountB;
    int nFlag;
    while(cin >> n)
    {
        if(n == 0)
        {
            break;
        }
        for(i = 0; i < n*2; i++)
        {
            cin >> x[i] >> y[i];
        }
        nFlag = 1;

        for(i = -500;nFlag == 1 && i < 501; i++)
        {
            for(j = -500;nFlag == 1 && j < 501; j++)
            {
                nCountA = 0;
                nCountB = 0;
                for(k = 0; k < n*2; k++)
                {
                    if(i * x[k] + j * y[k] == 0)
                    {
                        break;
                    }
                    if(i * x[k]+ j * y[k] < 0)
                    {
                        nCountB++;
                    }
                    else
                    {
                        nCountA++;
                    }
                }
                if(k == n*2 && nCountB  == nCountA && nCountA == n)
                {
                    nFlag = 0;
                    cout << i << " " << j << endl ;
                }
            }
        }
    }
       return 0;
}
