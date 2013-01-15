/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>

const int MAXN=110;

int a[MAXN];
int n;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif

    while(scanf("%d",&n)==1 && n)
    {
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);

        int k=a[1];

        for(int i=2;i<=n;i++)
            k^=a[i];
        int ans=0;
        for(int i=1;i<=n;i++)
            if((k^a[i])<a[i])
                ans++;

        printf("%d\n",ans);
    }

    return 0;
}
