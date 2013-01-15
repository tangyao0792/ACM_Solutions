#include<iostream>
#include<cmath>
#include<cstdio>

#define ESP 1e-15
using namespace std;

int p ,q, r, s, t, u;

double fun(double x);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while(cin >> p >> q >> r >> s >> t >> u)
    {
        double left = 0;
        double right = 1;
        double mid;

        if(fun(left) * fun(right) > ESP)
        {
            printf("No solution\n");
            continue;
        }
        while( right - left > ESP)
        {
            mid = (left+right)/2;
            if( fun(mid) * fun(left) < ESP)
            {
                right = mid;
            }
            else
            {
                left = mid;
            }
        }
        printf("%.4lf\n", mid);
    }
    return 0;
}

double fun(double x)
{
    double sum = 0;
    sum = p * exp(-x) + q * sin(x) + r * cos(x) +
    s * tan(x) + t * x * x + u;
    return sum;

}
