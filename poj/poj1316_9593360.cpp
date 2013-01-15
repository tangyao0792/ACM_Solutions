#include<iostream>

using namespace std;

int main()
{
    int num,sum,i;
    char flag[10001];
    for(i = 1; i < 10001; i++)
    {
        flag[i] = 1;
    }
    for(i = 1; i < 10001; i++)
    {
        num = i;
        sum = 0;
        while(num != 0)
        {
            sum += num%10;
            num /= 10;
        }
        num =i + sum;
        if(num < 10001)
        {
            flag[num] = 2;
        }
    }

    for(i = 1; i < 10001; i++)
    {
        if(flag[i] == 1)
        {
            cout << i << endl;
        }
    }

    return 0;
}
