#include<iostream>
#include<algorithm>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

int n;
int in[1000100];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int i;
    while(cin >> n)
    {
        for(i = 0; i < n; i++)
        {
            cin >> in[i];
        }
        sort(in, in+n);
        int l = (n-1)/2;
        int cnt = 0, p = 1;
        if( n%2==0)
        {
            for(i=l;i>=0&&in[l]==in[i];i--)cnt++;
            for(i=l+1;i<n&&in[i]==in[l+1];i++)cnt++;

            p = in[l+1]-in[l]+1;
        }
        else
        {
            for(i=l;i>=0&&in[l]==in[i];i--)cnt++;
            for(i=l+1;i<n&&in[i]==in[l];i++)cnt++;
            p = 1;
        }
        cout << in[l]<<" "<<cnt<<" "<<p<<endl;

    }
    return 0;
}
