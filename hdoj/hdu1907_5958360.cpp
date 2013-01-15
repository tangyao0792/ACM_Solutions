/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r",stdin);
   // freopen("out.txt","w",stdout);
#endif

    int t,n;

    scanf("%d",&t);

    while(t--)
    {
        scanf("%d",&n);
        int ans=0;
        bool flag=false;        //是否出现1以外的数
        for(int i=0;i<n;i++)
        {
            int tmp;
            scanf("%d",&tmp);

            if(tmp>1)flag=true;


            ans^=tmp;
        }

        if(flag)
        {
            if(ans)
                puts("John");
            else
                puts("Brother");
        }
        else
        {
            if(ans)
                puts("Brother");
            else
                puts("John");
        }

    }

    return 0;
}
