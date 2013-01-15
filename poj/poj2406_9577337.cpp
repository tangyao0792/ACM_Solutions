#include<iostream>
#include<string.h>

using namespace std;

char input[1000010];
int next[1000010];
int length;
void make_next();

int main()
{
    while(cin >> input && input[0] != '.')
    {
        length = strlen(input);
        make_next();
        if((length) % (length-next[length]) == 0)
        {
            cout << (length) / (length-next[length])<<endl;
        }
        else
        {
            cout << 1 << endl;
        }

    }
    return 0;
}

void make_next()
{
    next[0] = -1;
    int i = 0;
    int j = - 1;

    while(i < length+1)
    {
        if(j == -1 || input[i] == input[j])
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
