#include<stdio.h>

long long exEuclid(__int64 a, __int64 b, long long  &x, long long &y);

int main()
{
    __int64 x, y, m, n, l;
    scanf("%I64d %I64d   %I64d %I64d %I64d",&x, &y, &m, &n, &l);
    __int64 a, b;
    __int64 r = exEuclid(m-n, l, a, b);
    if((y - x) % r != 0)
    {
        printf("Impossible\n");
    }
    else
    {
        __int64 time = l /r;
        if(time < 0)
        {
            time = -time;
        }
        a = a * ( (y-x) / r);
        b = b * ( (y-x) / r);
        a = a % time;
        if(a < 0)
        {
            a += time;
        }
        printf("%I64d\n",a);
    }
    return 0;
}

long long exEuclid(__int64 a, __int64 b, long long &x, long long &y)
{
    if(b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    __int64 r = exEuclid(b, a % b, x, y);
    __int64 temp = x;
    x = y;
    y = temp -(a/b) * y;
    return r;
}
