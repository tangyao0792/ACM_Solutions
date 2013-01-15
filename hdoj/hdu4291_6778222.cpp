/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

typedef long long ULL;

const long long MOD=1e9+7;
const int size=2;

class Matrix
{
    public :
        ULL mat[size][size];
        int cnt;

        Matrix operator +  (const Matrix &tmp) const
        {

            Matrix ans;
            ans.cnt=tmp.cnt;
            memset(ans.mat,0,sizeof(ans.mat));
            for(int i=0;i<cnt;i++)
                for(int j=0;j<cnt;j++)
                    ans.mat[i][j]=tmp.mat[i][j]+mat[i][j];
            return ans;
        }
        Matrix operator % (long long mod)
        {
            for(int i=0;i<cnt;i++)
                for(int j=0;j<cnt;j++)
                    mat[i][j]%=mod;
            return *this;
        }
};
Matrix mul  (Matrix a, Matrix &tmp,long long mod)
    {

        Matrix ans;

        memset(ans.mat,0,sizeof(ans.mat));
        ans.cnt=tmp.cnt;
        for(int i=0;i<a.cnt;i++)
            for(int j=0;j<a.cnt;j++)
            {

                ans.mat[i][j]=0;
                for(int k=0;k<a.cnt;k++)
                    ans.mat[i][j]+=a.mat[i][k]*tmp.mat[k][j]%mod;
            }
        return ans;
    }



long long Pow(Matrix a,long long b,long long mod)
{
    if(b<=0)
    {
        return 1;
    }

    Matrix r;
    r.cnt=a.cnt;
    memset(r.mat,0,sizeof(r.mat));
    for(int i=0;i<r.cnt;i++)
        r.mat[i][i]=1;
    while(b)
    {

        if(b&1LL)r=mul(r,a,mod);
//        a=a*a%mod;
        a=mul(a,a,mod);
        b>>=1;
    }
    return r.mat[0][0]%mod;
}

long long get(long long k,long long mod=MOD)
{
    k--;

    Matrix a;
    a.cnt=2;
    a.mat[0][0]=3;
    a.mat[0][1]=1;
    a.mat[1][0]=1;
    a.mat[1][1]=0;

    if(k<0)
        return 0;
    long long c=Pow(a,k,mod);
    return c;
}

inline long long getans(long long n)
{
    return get(get(get(n,183120),222222224),MOD);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in","r",stdin);
#endif


    long long a;
#ifndef ONLINE_JUDGE
    while(scanf("%lld",&a)==1)
        printf("%lld\n",getans(a));
#else
    while(scanf("%I64d",&a)==1)
        printf("%I64d\n",getans(a));
#endif
    return 0;
}
