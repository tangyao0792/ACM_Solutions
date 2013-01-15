/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

int main(int argc, const char *argv[])
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    char str[100];
    int a[100],b[100];
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int sn;
        scanf("%d %s",&sn,str);
        int n=strlen(str);
        for(int i=0;i<n;i++)
        {
            b[i]=a[i]=str[i]-'0';
        }
        next_permutation(b,b+n);
        bool flag=false;
        for(int i=0;i<n-1;i++)
        {
            if(b[i]>b[i+1])
                flag=true;

        }
        if(!flag)
        {
            printf("%d BIGGEST\n",sn);
        }
        else
        {
            printf("%d ",sn);
            for(int i=0;i<n;i++)
                printf("%d",b[i]);
            puts("");
        }
    }
    return 0;
}
