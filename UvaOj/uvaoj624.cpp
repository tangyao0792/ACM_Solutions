#include<iostream>
#include<sstream>
#include<cstring>
#include<stack>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

int w[25];
int f[25][10005];
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    string line;
    while(getline(cin, line)&&line.size() != 0)
    {
        memset(f, 0, sizeof(f));
        int space, num;
        stringstream ss(line);
        ss >> space >> num;
        for(int i = 1; i <= num; i++)
        {
            ss >> w[i];
        }
        for(int i = num; i >= 1; i--)
        {
            for(int v = 0; v <= space; v++)
            {
                if(v <w[i])
                {
                    f[i][v] = f[i+1][v];
                }
                else
                {
                    f[i][v] = max(f[i+1][v],f[i+1][v-w[i]]+w[i]);
                }
            }
        }
        int cur = f[1][space];
        for(int i = 1; i <= num; i++)
        {
            if(f[i+1][cur-w[i]]+w[i] == cur)
            {
                cur -= w[i];
                cout << w[i] << " ";
            }
        }

        cout << "sum:"<<f[1][space]<<endl;
    }
    return 0;
}
