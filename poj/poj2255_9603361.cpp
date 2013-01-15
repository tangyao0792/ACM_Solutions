#include<iostream>
#include<string.h>

using namespace std;

char pre[27],in[27];
int step;
void fun( int first, int last);

int main()
{
    int length;
    while(cin >> pre >> in)
    {
        step = 0;
        length = strlen(pre);
        fun(0,length);
        cout << endl;
    }
    return 0;
}

void fun(int first, int last)
{

    int i = first;
    for(; i < last; i++)
    {
        if(pre[step] == in[i])
        {
            step++;
            fun(first,i);
            fun(i+1,last);
            cout << in[i];
            return;
        }
    }
}
