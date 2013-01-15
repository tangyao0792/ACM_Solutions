/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>

using namespace std;


int a[11];

int main(int argc, const char *argv[])
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int sn;
        scanf("%d",&sn);
        for(int i=1;i<=10;i++)
            scanf("%d",&a[i]);
        int ans=0;
        for(int i=0;i<3;i++)
        {
            int p=-1;
            for(int j=1;j<=10;j++)
            {
                if(p==-1 || a[p]<a[j])
                    p=j;
            }
            if(i==2)
                ans=a[p];
            a[p]=-1;
        }
        printf("%d %d\n",sn,ans);
    }
    return 0;
}
