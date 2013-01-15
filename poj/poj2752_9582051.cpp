#include<iostream>
#include<string.h>

using namespace std;

void make_next();
void show_result(int step);
char str[400010];
int next[400010];
int length;

int main()
{
    while( cin >> str)
    {
        length = strlen(str);
        make_next();
        show_result(length);
        cout << length << endl;
    }
    return 0;
}

void show_result(int step)
{
    if(next[step] > 0)
    {
        show_result(next[step]);
        cout << next[step] << " ";
    }

}
void make_next()
{
    next[0] = -1;
    int i = 0;
    int j = -1;
    while(i < length+1)
    {
        if(j == -1 || str[i] == str[j])
        {
            i++;
            j++;
            next[i] = j;
        }
        else
        {
            j = next[j];
        }
    }

}
