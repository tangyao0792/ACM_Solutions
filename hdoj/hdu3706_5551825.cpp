/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cmath>
#include<iostream>

#define min(x,y) (x<y?x:y)

using namespace std;

const int MAXN=10000010;

int st[MAXN];
int a,b,n;

void SparseTable()
{
    int k=int(log(double(a+1))/log(2.0));
    for(int j=1;j<=k; j++)
    {
        for(int i=2;i<=a && i<=n;i++)
                st[i]=min(st[i],st[i-1]);
        for(int i=a+1;i<=n; i++)
            if(i-(1<<(j-1)>0))
                st[i]=min(st[i],st[i-(1<<(j-1))]);
    }
}

int get(int i)
{
    if(i-a<1)   return st[i];
    int k=int(log(double(a+1))/log(2.0));

    return min(st[i],st[1+i-(1<<k)]);

}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d %d %d",&n,&a,&b)==3)
    {
        st[1]=a%b;
        for(int i=2;i<=n;i++)
        {
            __int64 tmp=st[i-1];
            tmp*=a;
            st[i]=tmp%b;
        }
        SparseTable();
        __int64 ans=1;
        for(int i=1;i<=n;i++)
        {
            ans=(ans*get(i))%b;
        }
        cout << ans << endl;
    }
    return 0;
}
