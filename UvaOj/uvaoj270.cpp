#include<iostream>
#include<sstream>
#include<algorithm>
#include<cmath>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

typedef struct
{
    int x, y;
}Point;

Point p[800];
double k[5000];
int  n;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase;
    string line;
    cin >> nCase;
    getline(cin, line);
    getline(cin, line);
    while( nCase--)
    {
        for(n = 0; getline(cin, line) && line.size() != 0; n++)
        {
            stringstream ss(line);
            ss >> p[n].x >> p[n].y;
        }
        int i, j, num, nStep, nMax, noK;
        num = 0;
        nMax = 0;
       for(i = 0; i < n; i++)
       {
           noK = 0;
           num = 0;
           nStep = 1;
           for(j = 0; j < n; j++)
           {
               if(i != j)
               {
                   if(p[i].x == p[j].x)
                   {
                       noK++;
                   }
                   else
                   {
                       k[num++] = (double(p[i].y - p[j].y)/(p[i].x - p[j].x));
                   }
                }
           }
           sort(k, k+num);
           for(j = 0; j < num-1; j++)
           {
               if(abs(k[j] - k[j+1]) < 1e-6 )
               {
                   nStep++;
               }
               else
               {
                   if(nStep > nMax)
                   {
                       nMax = nStep;
                   }
                   nStep = 1;
               }
           }
            if(nStep > nMax)
            {
                nMax = nStep;
            }
           if(noK > nMax)
           {
               nMax = noK;
           }
       }
       cout << nMax+1 << endl;
       if(nCase != 0)
       {
           cout << endl;
       }
    }
    return 0;
}
