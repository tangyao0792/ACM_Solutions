#include<iostream>

using namespace std;

int num[10];
int temp[10];
int code[1010];
int guess[1010];

int main()
{
    int n;
    int i;
    int flag;
    int nCount = 0;
    int nStrong, nWeak;
    while(cin >> n && n != 0)
    {
        nCount++;
        cout << "Game " << nCount << ":" << endl;
        for(i = 0; i < 10; i++)
        {
            num[i] = temp[i] = 0;
        }

        for(i = 0; i < n; i++)
        {
            cin >> code[i];
            num[code[i]]++;
        }

        while(1)
        {
            nStrong = nWeak = 0;
            for(i = 0; i < 10; i++)
            {
                temp[i] = 0;
            }
            flag = 0;
            for(i = 0; i < n; i++)
            {
                cin >> guess[i];
                flag += guess[i];
                temp[guess[i]]++;
            }
            if(flag == 0)
            {
                break;
            }

            for(i = 0; i < n; i++)
            {
                if(code[i] == guess[i])
                {
                    nStrong++;
                }
            }

            for(i = 0; i < 10; i++)
            {
                if(num[i] < temp[i])
                {
                    nWeak += num[i];
                }
                else
                {
                    nWeak += temp[i];
                }
            }
            nWeak -= nStrong;
            cout << "    (" << nStrong <<"," << nWeak << ")" << endl;
        }


    }
    return 0;
}
