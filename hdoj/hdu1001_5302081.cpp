/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<iostream>

using namespace std;

int main()
{
    int n;
    while(cin>>n)
    {
        if(n%2 ==0)
        {
            cout << n/2*(n+1)<<endl<<endl;
        }
        else
        {
            cout <<(n+1)/2*n<<endl<<endl;
        }
    }
    return 0;
}
