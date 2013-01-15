#include<iostream>
#include<string.h>
#include<stdlib.h>

using namespace std;

char input[101][7];
char dic[101][7];
char scr[7];
const char signal[7] = "XXXXXX";

int cmp(const void *a,const void * b);

int main()
{
    int i, j, k, l;
    int length;
    int flag;
    char temp;
    i = 0;
    while(cin >> input[i] && strcmp(input[i],signal) != 0)
    {
        i++;
    }
    qsort(input,i, sizeof(char) * 7,cmp);
    for(j = 0; j < i; j++)
    {
        strcpy(dic[j],input[j]);
        length = strlen(input[j]);

        for(k = 0; k < length; k++)
        {
            for(l = 0; l < length -1 -k; l++)
            {
                if(dic[j][l] > dic[j][l+1])
                {
                    temp = dic[j][l];
                    dic[j][l] = dic[j][l+1];
                    dic[j][l+1] = temp;
                }
            }
        }
    }
    while(cin >> scr && strcmp(scr,signal) != 0)
    {
        length = strlen(scr);
        for(k = 0; k < length; k++)
        {
            for(l = 0; l < length -1 -k; l++)
            {
                if(scr[l] > scr[l+1])
                {
                    temp = scr[l];
                    scr[l] = scr[l+1];
                    scr[l+1] = temp;
                }
            }
        }


        flag = 0;
        for(k = 0; k < i; k++)
        {
            if(strcmp(scr,dic[k]) == 0)
            {
                flag = 1;
                cout << input[k] << endl;
            }
        }
        if(flag == 0)
        {
            cout << "NOT A VALID WORD" << endl;
        }
        cout << "******" << endl;

    }

    return 0;
}

int cmp(const void *a, const void *b)
{
    return strcmp((char*)(a),(char*)(b));
}
