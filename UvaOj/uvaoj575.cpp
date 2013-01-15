#include<iostream>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;


int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    string input;
    while(getline(cin,input))
    {
        if(input.size() == 1 && input[0] == '0')
        {
            break;
        }
        int len = input.size();
        int sum= 0;
        for(int i = 0; i < len; i++)
        {
            int seed = ((1<<(len-i))-1);
            sum += seed * (input[i]-'0');
        }
        cout << sum << endl;
    }
    return 0;
}
