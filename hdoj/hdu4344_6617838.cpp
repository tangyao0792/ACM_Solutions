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
#include<fstream>
using namespace std;
#define MAXN 10
#define C 16381
typedef long long  I64;
typedef long long LL;
map<I64,int> fac;


LL MultMod(LL a,LL b,LL n){
    a%=n;
    b%=n;
    LL ret=0;
    while(b){
        if(b&1){
            ret+=a;
            if(ret>=n) ret-=n;
        }
        a=a<<1;
        if(a>=n) a-=n;
        b=b>>1;
    }
    return ret;
}
LL PowMod(LL a,LL n,LL m){
    LL ret=1;
    a=a%m;
    while(n>=1){
        if(n&1)
            ret=MultMod(ret,a,m);
        a=MultMod(a,a,m);
        n=n>>1;
    }
    return ret;
}
bool Witness(LL a,LL n){
    LL t=0,u=n-1;
    while(!(u&1)){
        t++;
        u/=2;
    }
    LL x0=PowMod(a,u,n);
    for(int i=1;i<=t;i++){
        LL x1=MultMod(x0,x0,n);
        if(x1==1&&x0!=1&&x0!=(n-1))
            return true;
        x0=x1;
    }
    if(x0!=1)
        return true;
    return false;
}
bool Miller_Rabin(LL n,int t=10){
    if(n==2) return true;
    if((n&1)==0)  return false;
    srand(time(NULL));
    for(int i=0;i<t;i++){
        LL a=rand()%(n-1)+1;
        if(Witness(a,n))
            return false;
    }
    return true;
}

//************

LL gcd(LL a, LL b){
    return b ? gcd(b, a % b) : a;
}

LL pollard_rho(LL n, LL c=16381){
    I64 x, y, d, i = 1, k = 2;
    srand((LL)time(0));
    x = ((LL) rand()) % (n - 1) + 1;
    y = x;
    while(1){
        i ++;
        x = (MultMod(x, x, n) + c) % n;
        d = gcd(y - x + n, n);
        if(d != 1 && d != n) return d;
        if(y == x) return n;
        if(i == k) y = x, k <<= 1;
    }
}

void find(LL n, LL c=16381){
    LL r;
    if(n <= 1) return;
    if(Miller_Rabin(n)){
        fac[n] ++;
        return;
    }
    r = pollard_rho(n, c--);
    find(n / r, c);
    find(r, c);
}

#define ll long long



ll Pow(ll a,ll b)

{

    ll r=1;

    while(b)

    {

        if(b&1LL)r=r*a;

        a=a*a;

        b>>=1;

    }

    return r;

}


int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    int T;
    scanf("%d",&T);
    while(T--)
    {
        long long x;
        cin >>x;
        if(Miller_Rabin(x,10))
        {
            cout<<1<<" "<<x<<endl;
            continue;
        }
        fac.clear();
        find(x,C);
        int cnt=0;
        ll sum=0;
        map<I64,int>::iterator it=fac.begin();
        ll last;
        for(;it!=fac.end();it++)
        {
            cnt++;
            sum+=Pow((*it).first,(*it).second);
            last=(*it).first;
        }
        if(cnt==1)
        {
            cout<<1<<" "<<sum/(last)<<endl;
        }
        else
        {
            cout<<cnt<<" "<<sum<<endl;
        }
    }
    return 0;
}
