/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

int sg[1001];
int flag[1001][1001];
int fib[100];
int a[3];

void swap(int &x,int &y)
{
    int tmp=x;
    x=y;
    y=tmp;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif

    memset(flag,0,sizeof(flag));
    int f1,f2,cnt;
    cnt=0;

    f1=1;
    f2=1;
    while(f1<=1000 && f2<=1000)
    {
        fib[cnt++]=f1;
        swap(f1,f2);
        f1=f2+f1;
    }

    for(int i=0;i<=1000;i++)
    {
        for(int j=0;j<cnt;j++)
        {
            if(i-fib[j]<0)
                break;

            flag[i][sg[i-fib[j]]]=1;
        }
        for(int j=0;j<=1000;j++)
            if(!flag[i][j])
            {
                sg[i]=j;
                break;
            }
    }

    while(true)
    {
        for(int i=0;i<3;i++)
            scanf("%d",&a[i]);

        if(!(a[0]*a[1]*a[2]))
            break;

        int ans=0;
        for(int i=0;i<3;i++)
            ans^=sg[a[i]];

        //flag[i]表示现在遇到i能赢

        if(!ans)
            printf("Nacci\n");
        else
            printf("Fibo\n");
    }

    return 0;
}
