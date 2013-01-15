/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

const int INF=1<<28;
const int MAXN=10010;

int a[MAXN];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r",stdin);
#endif
    int maxSum,curSum;
    int n,x,st,end;

    while(scanf("%d",&n)==1 && n)
    {
        maxSum=-INF;curSum=0;
        st=end=x=1;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            curSum+=a[i];

            if(curSum>maxSum)
            {
                maxSum=curSum;
                st=x;
                end=i;
            }
            if(curSum<0 || i==1)
            {
                curSum=0;
                x=i+1;
            }
        }
        if(maxSum>=0)
            printf("%d %d %d\n",maxSum,a[st],a[end]);
        else
            printf("%d %d %d\n",0,a[1],a[n]);
    }


    return 0;
}
