#include<iostream>
#include<math.h>

#ifndef ONLINE_JUDGE
    #include<stdio.h>
#endif

using namespace std;

typedef struct
{
    int x, y;
}Point;

Point dot[10];
int order[10];
int tempOrder[10];
double minDis;
int n;

void backtracking(int step);
double CalculateDistance(Point d1, Point d2);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif

    int nCount = 0;
    int i;
    while(cin >> n)
    {
        if(n == 0)
        {
            break;
        }
        nCount++;
        cout << "**********************************************************"
            << endl << "Network #" << nCount << endl;
        for(i = 0; i < n; i++)
        {
            cin >> dot[i].x >> dot[i].y;
        }
        minDis = 1e+20;
        backtracking(0);
        cout.setf(ios::fixed);
        cout.precision(2);
        for(i = 0; i < n-1; i++)
        {

            cout << "Cable requirement to connect (" << dot[tempOrder[i]].x
                << "," << dot[tempOrder[i]].y << ") to ("
                << dot[tempOrder[i+1]].x << "," << dot[tempOrder[i+1]].y <<") is "
                << CalculateDistance(dot[tempOrder[i]],dot[tempOrder[i+1]])
                <<" feet."  <<endl;
        }
        cout << "Number of feet of cable required is "<< minDis <<"." << endl;
    }
    return 0;
}

void backtracking(int step)
{
    int i, j, ok;
    double sum;
    if(step == n)
    {
        sum = 0;
        for(i = 0; i < n-1; i++)
        {
            sum += CalculateDistance(dot[order[i]],dot[order[i+1]]);
        }
        if(sum < minDis)
        {
            minDis = sum;
            for(i = 0; i < n; i++)
            {
                tempOrder[i] = order[i];
            }
        }
    }
    for(i = 0; i < n; i++)
    {
        order[step] = i;
        ok = 1;
        for(j = 0; j < step; j++)
        {
            if(order[step] == order[j])
            {
                ok = 0;
                break;
            }
        }
        if(ok == 1)
        {
            backtracking(step+1);
        }
    }
}

double CalculateDistance(Point d1, Point d2)
{
    int x = d1.x-d2.x;
    int y = d1.y-d2.y;
    double dis = sqrt(x*x+y*y);
    return dis + 16;
}
