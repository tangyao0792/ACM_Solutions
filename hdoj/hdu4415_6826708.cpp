/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;

const int MAXN=110000;

int a[MAXN],b[MAXN],c[MAXN];
//a: bi==0  b: bi!=0
int na,nb,nc;
int n,m;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif

    int t;
    scanf("%d",&t);
    int nt=1;
    while(t--)
    {
        scanf("%d %d",&n,&m);
        na=nb=nc=0;
        int sumb=0;
        for(int i=0;i<n;i++)
        {
            int ai,bi;
            scanf("%d %d",&ai,&bi);
            sumb+=bi;
            if(bi==0)
            {
                a[na++]=ai;
            }
            else
            {
                b[nb++]=ai;
            }
        }
        if(na)
            sort(a,a+na);
        if(nb)
            sort(b,b+nb);

        int cost=0,kill=0;
        int free=0;

        if(b[0]<=m)
        {
            free=sumb-nb+1;
            cost=b[0];
            kill=nb;
        }
        else
        {
            free=0;
            cost=0;
            kill=0;
        }

        if(free>=na)
        {
            kill=n;
        }
        else
        {
            kill+=free;
            for(int i=1;i<nb;i++)
                c[nc++]=b[i];
            for(int i=0;i<na-free;i++)
                c[nc++]=a[i];
            if(nc)
                sort(c,c+nc);

            for(int i=0;i<nc && i<na-free;i++)
            {
                if(cost+c[i]>m)
                    break;
                cost+=c[i];
                kill++;
            }
        }

        if(na)
        {
            int tmpc=0,tmpk=0;
            for(int i=0;i<na;i++)
            {
                if(tmpc+a[i]>m)
                    break;
                tmpc+=a[i];
                tmpk++;
            }
            if(tmpk>kill || (tmpk==kill && tmpc<cost))
            {
                kill=tmpk;
                cost=tmpc;
            }
        }
        printf("Case %d: %d %d\n",nt++,kill>n?n:kill,cost);
    }


    return 0;
}
