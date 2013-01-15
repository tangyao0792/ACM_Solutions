#include<iostream>
#include<string.h>
using namespace std;

int main()
{
    int num[1010], period[1010];
    char input[20];
    int i = 0;
    char reg[] = "Register";
    while(cin >> input)
    {
        if(input[0] == '#')
        {
            break;
        }
        cin >> num[i] >> period[i];
        i++;
    }
    int temp[1010];

    for(int j = 0; j < i; j++)
    {
        for(int k = 0; k < i - j -1; k++)
        {
            if(num[k] > num[k+1])
            {
                int tmp = num[k];
                num[k] = num[k+1];
                num[k+1] = tmp;

                tmp = period[k];
                period[k] = period[k+1];
                period[k+1] = tmp;
            }
        }
    }
    for(int j = 0; j < i; j++)
    {
        temp[j] = period[j];
    }
    int n;
    cin >> n;
    int j = 0;
    while(j < n)
    {
        for(int k = 0; k < i; k++)
        {
            if(temp[k] == 0)
            {
                continue;
            }
            period[k]--;
            if(period[k] == 0)
            {
                period[k] = temp[k];
                cout << num[k] << endl;
                j++;
            }
            if(j == n)
            {
                break;
            }
        }
    }
    return 0;
}
