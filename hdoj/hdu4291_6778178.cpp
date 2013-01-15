/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<stdio.h>
 #include<stdlib.h>
 #include<string.h>
 typedef __int64 LL;
 struct Matrix
 {
     LL Mt[2][2];
     void init0(){memset(Mt, 0, sizeof(Mt));}
     void init1() {init0(), Mt[0][0] = Mt[1][1] = 1;}
     Matrix(){init0();}
     Matrix(LL num) {init0();Mt[0][0] = Mt[1][1] = num;}
     Matrix(LL a, LL b, LL c, LL d){Mt[0][0] = a, Mt[0][1] = b, Mt[1][0] = c, Mt[1][1] = d;}
     Matrix Mul(const Matrix &b, LL mod)
     {
         int i, j, k;Matrix res;
         for(i = 0; i < 2; ++ i)
             for(j = 0; j < 2; ++ j)
                 for(k = 0; k < 2; ++ k)
                     res.Mt[i][j] = (res.Mt[i][j] + Mt[i][k] * b.Mt[k][j]) % mod;
         return res;
     }
     Matrix Rep(LL p, LL mod)
     {
         Matrix b = *this, res(1);
         if(p == 0) return res;
         if(p == 1) return b;
         while(p > 1)
         {
             if(p & 1) res = res.Mul(b, mod);
             b = b.Mul(b, mod);
             p >>= 1;
         }
         return b.Mul(res, mod);
     }
 };
 LL Cal(LL n, LL mod)
 {
     Matrix mm(3, 1, 1, 0), ori(1, 0, 0, 0);
     if(!n) return 0;
     return ori.Mul(mm.Rep(n - 1, mod), mod).Mt[0][0];
 }
 int main()
 {
     LL n;
     while(scanf("%I64d", &n) != EOF)
         printf("%I64d\n", Cal(Cal(Cal(n, 183120), 222222224), 1000000007));
     return 0;
 }
