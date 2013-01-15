/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <map>
#include <iostream>
#include <ostream>
#include<vector>
#include<cstring>

using namespace std;

#define MAXN 10
#define C 16381
typedef long long  I64;
typedef long long LL;
map<I64,int> fac;
//find(n,C)


typedef long long LL;

int n,m;
int qx[1111],qy[1111],cnt;
LL fact[1111],nf;
inline I64 multi(I64 a, I64 b, I64 n){

    I64 tmp = a % n, s = 0;
    while(b){

        if(b & 1){

            s = (s + tmp);
            if(s >= n ) s -= n;
        }
        tmp = (tmp + tmp);
        if( tmp >= n )  tmp -= n;
        b >>= 1;
    }
    return s;
}

inline I64 Pow(I64 a, I64 b, I64 n){

    I64 tmp = a % n, s = 1;
    while(b){

        if(b & 1) s = multi(s, tmp, n);
        tmp = multi(tmp, tmp, n);
        b >>= 1;
    }
    return s;
}

inline int witness(I64 a, I64 n){

    I64 u = n - 1, t = 0, i, x, y;
    while(!(u & 1))    u >>= 1, t ++;
    x = Pow(a, u, n);
    for(i = 1; i <= t; i ++){

        y = multi(x, x, n);
        if(y == 1 && x != 1 && x != n -1) return 1;
        x = y;
    }
    if(x != 1) return 1;
    return 0;
}

inline int test(I64 n){

    I64 a;
    int i;
    if(n == 2) return 1;
    if(n < 2 || !(n & 1)) return 0;
    srand((I64)time(0));
    for(i = 0; i < MAXN; i ++){

        a = ((I64) rand()) % (n - 2) + 2;
        if(witness(a, n)) return 0;
    }
    return 1;
}

inline I64 gcd(I64 a, I64 b){

    return b ? gcd(b, a % b) : a;
}

inline I64 pollard_rho(I64 n, I64 c){

    I64 x, y, d, i = 1, k = 2;
    srand((I64)time(0));
    x = ((I64) rand()) % (n - 1) + 1;
    y = x;
    while(1){

        i ++;
        x = (multi(x, x, n) + c) % n;
        d = gcd(y - x + n, n);
        if(d != 1 && d != n) return d;
        if(y == x) return n;
        if(i == k) y = x, k <<= 1;
    }
}

inline void find(I64 n, I64 c){

    I64 r;
    if(n <= 1) return;
    if(test(n)){

        fac[n] ++;
        return;
    }
    r = pollard_rho(n, c--);
    find(n / r, c);
    find(r, c);
}


inline void sep(int p)
{
    nf=0;
    fac.clear();
    find((LL)(p),C);
    map<I64,int>::iterator it=fac.begin();
    for(;it!=fac.end();it++)
    {
        fact[nf++]=it->first;
    }
}
//LL sum(int k,int d)
//{
//    if(d==nf)
//    {
//        return LL(k+1)*k/2;
//    }
//    return sum(k,d+1)-sum(k/fact[d],d+1)*fact[d];
//}

inline LL sum(int k,int p)
{
    LL ans=(LL)(1+k)*k/2;

    int size=1<<nf;
    for(int i=1;i<size;i++)
    {
        int t=0;
        LL s=1;
        for(int j=0;(1<<j)<=i;j++)
        {
            if(i&(1<<j))
            {
                t++;
                s*=fact[j];
            }
        }
        int f;
        if(t%2==0)
            f=1;
        else
            f=-1;

        LL tb=LL(k)/s;

        if(f==1)
        {
            ans+=s*(1+tb)*tb/2;
        }
        else
        {
            ans-=s*(1+tb)*tb/2;
        }
    }
    return ans;
}

int pos[401000];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif

    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %d",&n,&m);
        memset(pos,-1,sizeof(pos));
        cnt=0;

        for(int i=0;i<m;i++)
        {
            int f;
            scanf("%d",&f);
            if(f==2)
            {
                int x,y;
                scanf("%d %d",&x,&y);
                if(pos[x]==-1)
                {
                    pos[x]=cnt++;
                }
                    qx[pos[x]]=x;
                    qy[pos[x]]=y ;

            }
            else
            {
                int x,y,p;
                scanf("%d %d %d",&x,&y,&p);
                sep(p);
//                LL ans=sum(y,0)-sum(x-1,0);
                LL ans=sum(y,p)-sum(x-1,p);
                for(int j=0;j<cnt;j++)
                {
                    if(qx[j]>y || qx[j]<x)
                        continue;
                    if(gcd(p,qx[j])==1ll)
                        ans-=qx[j];
                    if(gcd(p,qy[j])==1ll)
                        ans+=qy[j];
                }
                printf("%I64d\n",ans);
            }
        }
    }
    return 0;
}
