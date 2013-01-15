#include<iostream>

#ifndef ONLINE_JUDGE
    #include<stdio.h>
#endif

using namespace std;

int p, n;
int nMin;
int led[110][20];
int  a[20];

int check();
void subset(int cur);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif

    int nCase;
    cin >> nCase;
    int i, j, k;

    for(i = 0; i < nCase; i++)
    {
        cin >> p >> n;
        for(j = 0; j < n; j++)
        {
            for(k = 0; k < p; k++)
            {
                cin >> led[j][k];
            }
        }
        nMin = 20;
        subset(0);
        cout << nMin << endl;
    }

    return 0;
}
int check()
{
    int i, j, k;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < i; j++)
        {
            for(k = 0; k < p; k++)
            {
                if(a[k] == 1 && led[i][k] != led[j][k])
                {
                    break;
                }
            }
            if(k == p)
            {
                return -1;
            }
        }
    }
    return 1;
}
void subset(int cur)
{
    int i, nCount;;
    if(cur == p)
    {
        if(check() == 1)
        {
            nCount = 0;
            for(i = 0; i < p; i++)
            {
                if(a[i] == 1)
                {
                    nCount++;
                }
            }
            if(nCount < nMin)
            {
                nMin = nCount;
            }
        }
        return;
    }
    a[cur] = 0;
    subset(cur+1);
    a[cur] = 1;
    subset(cur+1);
}
