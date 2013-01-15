#include<iostream>

using namespace std;

int half( int a);

int main()
{
    char input[100];
    char flag;
    int distance,sum;
    sum = 0;
    while(cin >> input)
    {
        if(input[0] == '0')
        {
            cout << sum << endl;
            sum = 0;
            continue;
        }
        else if(input[0] == '#')
        {
            break;
        }
        cin >> input;
        cin >> distance;
        cin >> flag;
        switch (flag)
        {
            case 'F': sum += distance * 2;break;
            case 'B': sum += distance + half(distance);break;
            case 'Y':
            if(distance < 500)
            {
                sum += 500;
            }
            else
            {
                sum += distance;
            }
            default:break;
        }
    }
    return 0;
}

int half(int a)
{
    int temp = a;
    temp = a / 2;
    if(a == temp * 2)
    {
        return temp;
    }
    return temp +1;
}
