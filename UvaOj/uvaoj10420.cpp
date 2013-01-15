#include<iostream>
#include<stdlib.h>
#include<set>
#include<string>
#include<string.h>
#include<sstream>

#include<stdio.h>


using namespace std;

typedef struct
{
    char szCountry[100];
    set<string> nName;
}listOfC;


int cmp(const void *a, const void *b);

int main()
{
    freopen("in.txt", "r", stdin);
    int n;
    cin >> n;
    int i, j, nCount;
    char szC[100];
    string szN;
    nCount = 0;
    listOfC li[2010];
    string aLine;
    getline(cin, aLine);
    for(i = 0; i < n; i++)
    {
        getline(cin, aLine);
        stringstream ss(aLine);
        ss >> szC;
        for(j = 0; j < nCount; j++)
        {
            if(strcmp(li[j].szCountry,szC) == 0)
            {
                break;
            }
        }
        if(j == nCount)
        {
            nCount++;
        }
        strcpy(li[j].szCountry, szC);
        getline(ss,szN);
        li[j].nName.insert(szN);
    }
    qsort(li,nCount,sizeof(listOfC),cmp);
    for(i = 0; i < nCount; i++)
    {
        cout << li[i].szCountry << " " << li[i].nName.size() << endl;
    }
    return 0;
}

int cmp(const void *a, const void *b)
{
    listOfC aa = *((listOfC*)a);
    listOfC bb = *((listOfC*)b);
    return (strcmp(aa.szCountry,bb.szCountry));
}
