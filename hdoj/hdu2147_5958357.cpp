/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

int n,m;


int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r",stdin);
#endif

    int n,m;

    while(scanf("%d %d",&n,&m)==2)
    {
        if(!n && !m)    break;

        if((!((2000-n+1)&1)) && m&1)
            printf("What a pity!\n");
        else
            printf("Wonderful!\n");
    }

    return 0;
}
