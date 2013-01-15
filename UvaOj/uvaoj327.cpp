#include<iostream>
#include<cstring>

#ifndef ONLINE_JUDGE
    #include<stdio.h>
#endif

using namespace std;

string input;
int num[26];
int aft[26];                    //后改变值的字母
int vis[26];                    //哪些字母需要输出

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif

    const char *p = "++";
    const char *s = "--";
    int i, nLen;
    int nFlag;          //之前是否有字母
    cout << strlen(s);
    while(getline(cin, input))
    {
        for(i = 0; i < 26; i++)
        {
            num[i] = i + 1;
            aft[i] = 0;
            vis[i] = 0;
        }
        nLen = input.size();
        nFlag = 0;
        for(i = 0; i < nLen; i++)         //去掉所有自反运算符
        {
            if(input[i] > 'a'-1 && input[i] < 'z'+1)
            {
                vis[input[i] - 'a'] = 1;
                nFlag = 1;
            }
            else if(strcmp(&input[i], p) == 0)
            {
                if(nFlag = 1)
                {
                    input[i] = input[i+1] = ' ';
                    aft[input[i] - 'a'] = 1;
                    nFlag = 0;
                }
            }
        }

    }
    return 0;
}
