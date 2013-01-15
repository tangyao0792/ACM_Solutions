#include<iostream>
#include<string.h>

using namespace std;

int main()
{
    int sum[120];
    memset(sum,0, sizeof(sum));
    char input[110];
    int i;
    while(cin >> input)
    {

        int length = strlen(input);
        if(length == 1 && input[0] == '0')
        {
            break;
        }
        int g = 0;
        for(i = 0; i < length ; i++)
        {
            int temp = sum[119-i] + input[length-i-1]-'0' + g;
            sum[119-i] = temp % 10;
            g = temp/10;
        }
        while(g != 0)
        {
            int temp = sum[119-i] + g;
            sum[119-i] = temp % 10;
            g = temp/10;
            i++;
        }
    }
    i = 0;
    while(sum[i] == 0)
    {
        i++;
    }
    for(; i < 120; i++)
    {
        cout << sum[i];
    }
    cout << endl;

    return 0;
}
