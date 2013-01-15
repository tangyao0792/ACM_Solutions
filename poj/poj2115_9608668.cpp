#include<stdio.h>
#include<math.h>

__int64 gcd(__int64 a, __int64 b, __int64 &x, __int64 &y);

int main()
{
    __int64 a, b, c, k;
    __int64 d, r, l;
    __int64 x, y;
    while( (scanf("%I64d %I64d %I64d %I64d",&a,&b,&c,&k) > 0) &&
           !(a == 0 && b == 0 && c == 0 && k == 0))
    {
        d = (__int64)pow(2,k);
        r = gcd(c,d,x,y);
        if((b-a) % r)
        {
            printf("FOREVER\n");
        }
        else
        {
            x = (b-a) / r * x  % d + d;
            x = x % (d / r);
            printf("%I64d\n",x);
        }
    }
    return 0;
}

__int64 gcd(__int64 a, __int64 b, __int64 &x, __int64 &y)
{
    if(b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    __int64 r = gcd(b , a % b, x, y);
    __int64 temp = x;
    x = y;
    y = temp - (a/b) * y;
    return r;
}
