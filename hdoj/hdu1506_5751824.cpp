/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

#define max(a,b) (a>b?a:b)

const int INF=1<<28;
const int MAXN=100010;
const int MAXM=1000000001;

typedef long long LL;

int n;
int left[MAXN],right[MAXN];
LL a[MAXN];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif

    while(scanf("%d",&n)==1 && n)
    {
        for(int i=1;i<=n;i++)
            scanf("%I64d",&a[i]);

        a[0]=-INF;a[n+1]=-INF;

        for(int i=1;i<=n;i++)
        {
            if(a[i]>a[i-1])
                left[i]=i;
            else
            {
                int t=left[i-1];
                while(a[i]<=a[t-1])
                {
                    t=left[t-1];
                }
                left[i]=t;
            }
        }

        for(int i=n;i>=1;i--)
        {
            if(a[i]>a[i+1])
                right[i]=i;
            else
            {
                int t=right[i+1];
                while(a[i]<=a[t+1])
                {
                    t=right[t+1];
                }
                right[i]=t;
            }
        }
        LL s=0;
        LL tmp;
        for(int i=1;i<=n;i++)
        {
            tmp=a[i]*(right[i]-left[i]+1);
            s=max(s,tmp);
        }
        printf("%I64d\n",s);
    }

    return 0;
}
