#include<iostream>
#include<cstring>

#ifndef ONLINE_JUDGE
    #include<stdio.h>
#endif

using namespace std;

string input;
int num[26];
int aft[26];                    //��ı�ֵ����ĸ
int vis[26];                    //��Щ��ĸ��Ҫ���

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif

    const char *p = "++";
    const char *s = "--";
    int i, nLen;
    int nFlag;          //֮ǰ�Ƿ�����ĸ
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
        for(i = 0; i < nLen; i++)         //ȥ�������Է������
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
