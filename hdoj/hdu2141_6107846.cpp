/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<iostream>
#include<algorithm>

using namespace std;

const int MAXN=505;

int a[MAXN],b[MAXN],c[MAXN];
int sum[MAXN*MAXN];

int l,n,m,s,p;

bool binarySearch(int x)
{
    int l=0,r=p-1;
    int mid;

    while(l<=r)
    {
        mid=(l+r)/2;
        
        if(sum[mid]==x)    
            return true;
        else if(sum[mid]<x)
            l=mid+1;
        else
            r=mid-1;
    }
    return false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    
    int nCase=1;
    while(scanf("%d %d %d",&l,&n,&m)==3)
    {
        for(int i=0;i<l;i++)    scanf("%d",&a[i]);
        for(int i=0;i<n;i++)    scanf("%d",&b[i]);
        for(int i=0;i<m;i++)    scanf("%d",&c[i]);

        p=0;

        for(int i=0;i<l;i++)
            for(int j=0;j<n;j++)
                sum[p++]=a[i]+b[j];

        sort(sum,sum+p);
        sort(c,c+m);

        printf("Case %d:\n",nCase++);
        scanf("%d",&s);
        while(s--)
        {
            int tmp;
            scanf("%d",&tmp);
            bool flag = false;
            for(int i=0;i<m && !flag;i++)
            {
                flag=binarySearch(tmp-c[i]);
            }
            if(flag)
                puts("YES");
            else
                puts("NO");
        }
    }

    return 0;
}
