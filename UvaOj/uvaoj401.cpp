#include<iostream>
#include<string.h>

using namespace std;

int main()
{
    char str[21];
    char letter[27] = "A...3..HIL.JM.O...2TUVWXY5";
    char num[10] = "1SE.Z..8.";
    int flagP, flagM;
    while(cin >> str)
    {
        int length = strlen(str);
        flagP = 1;
        flagM = 1;
        int i;
        for(i = 0; i < length/2+1; i++)
        {
            if(str[i] > 'A' -1 && str[i] < 'Z' +1)
            {
                if(letter[str[i]-'A'] != str[length-i-1])
                {
                    flagM = 0;
                    break;
                }
            }
            else
            {
                if(str[length-i-1] != num[str[i]-'1'])
                {
                    flagM = 0;
                    break;
                }
            }
        }

        for(i = 0; i < length/2+1; i++)
        {
            if(str[i] != str[length-i-1])
            {
                flagP = 0;
                break;
            }
        }

        if(flagM == 1 && flagP == 1)
        {
            cout << str << " -- is a mirrored palindrome." << endl;

        }
        else if(flagM == 1)
        {
            cout << str << " -- is a mirrored string." << endl;
        }
        else if(flagP == 1)
        {
            cout << str << " -- is a regular palindrome." << endl;
        }
        else
        {
            cout << str << " -- is not a palindrome." << endl;
        }
        cout << endl;
    }
    return 0;
}
