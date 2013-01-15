#include<iostream>
#include<string.h>
using namespace std;

int main()
{
    const char end_of_input[] = "ENDOFINPUT";
    const char end_a_line[] = "END";
    const char start_a_line[] = "START";
    int length;
    char input[1000];

    while( cin >> input && strcmp(input, end_of_input) != 0)
    {
        if(strcmp(input, start_a_line) == 0)
        {
            continue;
        }
        if(strcmp(input, end_a_line) == 0)
        {
            cout << endl;
            continue;
        }
        length = strlen( input);
        for(int i = 0 ; i < length; i++)
        {
            if(input[i] > 'A'-1 && input[i] < 'Z'+1)
            {
                input[i] = input[i] - 5;
                if(input[i] < 'A')
                {
                    input[i] +=26;
                }
            }
        }
        cout << input << " ";
    }
    return 0;
}
