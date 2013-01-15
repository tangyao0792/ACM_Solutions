/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;

const int INF=1<<28;
const int MAXN=1010;

char map[MAXN][MAXN];
int nLeft[MAXN],nRight[MAXN],a[MAXN];
int n,m;

int solve(int r)
{
    if(r==n)
    {
        for(int i=1;i<=m;i++)
        {
            int j=r;

            for(;j>0;j--)
                if(map[j][i]=='R')
                    break;

            a[i]=r-j;
        }
    }
    else
    {
        for(int i=1;i<=m;i++)
        {
            a[i]--;
            if(a[i]<0)
            {
                int j=r;

                for(;j>0;j--)
                    if(map[j][i]=='R')
                        break;

                a[i]=r-j;
            }
        }
    }


    a[0]=-INF;a[m+1]=-INF;

    for(int i=1;i<=m;i++)
    {
        if(a[i]>a[i-1])
            nLeft[i]=i;
        else
        {
            int t=nLeft[i-1];
            while(a[i]<=a[t-1])
            {
                t=nLeft[t-1];
            }
            nLeft[i]=t;
        }
    }

    for(int i=m;i>=1;i--)
    {
        if(a[i]>a[i+1])
            nRight[i]=i;
        else
        {
            int t=nRight[i+1];
            while(a[i]<=a[t+1])
            {
                t=nRight[t+1];
            }
            nRight[i]=t;
        }
    }

    int s=0;
    int tmp;
    for(int i=1;i<=n;i++)
    {
        tmp=a[i]*(nRight[i]-nLeft[i]+1);
        s=max(s,tmp);
    }
    return s;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif

    int K;
    cin>>K;
    while(K--)
    {
        cin>>n>>m;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                cin>>map[i][j];

        int ans=0;
        for(int i=n;i>=1;i--)
        {
            int  tmp=solve(i);
            ans=max(tmp,ans);
        }
        printf("%d\n",3*ans);
    }

    return 0;
}
