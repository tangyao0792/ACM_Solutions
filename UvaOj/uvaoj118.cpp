#include<iostream>
#include<string>
#include<sstream>
#include<cstring>
#include<algorithm>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

int w[15];

int convert(char *word);
bool comp(int a, int b);
int solve(int n);
int min(int a, int b, int c);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    string st;
    char word[6];
    while( getline(cin, st))
    {
        memset(w, 0, 15 * sizeof(int));
        stringstream ss(st);
        int nCount = 0;
        while(ss >> word)
        {
            w[nCount] = convert(word);
            nCount++;
        }
        sort(w, w+nCount, comp);
        int c = solve(nCount);
        cout << st << endl;
        cout << c << endl << endl;
    }
    return 0;
}

int min(int a, int b)
{
    if(a > b)
    {
        return b;
    }
    return a;
}

int solve(int n)
{
    int c = w[n-1];
    int a , b;
    int i, j;

    for(i = 0; i < n; i++)
    {
        a = (c / w[i]);
        for(j = i+1; j < n; j++)
        {
            b = (c / w[j]);
            if(a % n == b % n)
            {
                c = min((a+1) * w[i],(b+1) * w[j] );
                i = -1;
                break;
            }
        }
    }
    return c;
}

bool comp(int a, int b)
{
    return a > b;
}

int convert(char *word)
{
    int num;
    int bit;
    bit = 1;
    int nLen = strlen(word);
    int i;
    num = 0;
    for(i = nLen - 1; i > -1; i--)
    {
        num += bit * (word[i] - 'a' +1);
        bit *= 32;
    }
    return num;

}
