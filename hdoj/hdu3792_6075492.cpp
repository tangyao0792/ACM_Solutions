/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

const int MAXN=100001;

bool flag[MAXN];
int num[MAXN];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif

    memset(flag,false,sizeof(flag));
    memset(num,0,sizeof(num));

    flag[2]=false;
    for(int i=2;i<MAXN;i++)
        if(!flag[i])
            for(int j=2;j*i<MAXN;j++)
                flag[j*i]=true;

    for(int i=5;i<MAXN;i++)
        if(!flag[i] && !flag[i-2])
            num[i]=num[i-1]+1;
        else
            num[i]=num[i-1];

    int n;
    while(scanf("%d",&n)==1 && n>=0)
    {
        printf("%d\n",num[n]);
    }
    return 0;
}
