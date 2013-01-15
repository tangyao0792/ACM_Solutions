/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

int n;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r",stdin);
#endif

    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        int ans=0;
        for(int i=0;i<n;i++)
        {
            int num,l;
            scanf("%d %d",&num,&l);
            ans^=num%(l+1);
        }
        if(ans)
            puts("No");
        else
            puts("Yes");
    }

    return 0;
}
