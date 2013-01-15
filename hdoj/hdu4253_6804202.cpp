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

const int MAXN=50100;
const int MAXM=100100;

int p[MAXN];

struct edge
{

    int u,v,c,x;
    bool operator < (const edge t) const
    {

        return c<t.c;
    }
}e[MAXM],ed[2][MAXM];

int cnt[2];
int n,m,k;

inline void merge(int x)
{

    int p0=0,p1=0;
    int pcnt=0;
    while(p0<cnt[0] && p1<cnt[1])
    {

        if(ed[0][p0].c+x < ed[1][p1].c)
        {

            e[pcnt++]=ed[0][p0++];
            e[pcnt-1].c+=x;
        }
        else
        {

            e[pcnt++]=ed[1][p1++];
        }
    }
    while(p0<cnt[0])
    {

        e[pcnt++]=ed[0][p0++];
        e[pcnt-1].c+=x;
    }
    while(p1<cnt[1])
    {

        e[pcnt++]=ed[1][p1++];
    }
}

inline int find(int x)
{
    return p[x]==-1?x:(p[x]=find(p[x]));
}
inline int kruskal(int n,int &ans,int mid)
{

    merge(mid);
    ans=0;
//    memset(p,-1,sizeof(p));
    for(int i=0;i<=n;i++)
        p[i]=-1;
    int k=0;
    for(int i=0;i<m;i++)
    {

        int x=find(e[i].u);
        int y=find(e[i].v);
        if(x!=y)
        {

            ans+=e[i].c;
            if(e[i].x==0)
            {
                k++;
                ans-=mid;
            }
            p[x]=y;
        }
    }
    return k;
}

int main()
{


#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    int nCase=1;

    while(scanf("%d %d %d",&n,&m,&k)==3)
    {
        cnt[0]=cnt[1]=0;
        for(int i=0;i<m;i++)
        {
            int a,b,c,x;
            scanf("%d %d %d %d",&a,&b,&c,&x);
            ed[x][cnt[x]].u=a;
            ed[x][cnt[x]].v=b;
            ed[x][cnt[x]].c=c;
            ed[x][cnt[x]].x=x;
            cnt[x]++;
        }
        int l=-101,r=101;
        sort(ed[0],ed[0]+cnt[0]);
        sort(ed[1],ed[1]+cnt[1]);
        int ans;

        while(l<=r)
        {

            int mid=(l+r)>>1;

            int low=kruskal(n,ans,mid);

            int up=kruskal(n,ans,mid-1);

            ans+=(up-k)*mid;

            if(low<=k && k<=up)
                break;

            if(low>k)
                l=mid+1;
            if(up<k)
                r=mid-1;
        }
        printf("Case %d: %d\n",nCase++,ans);
    }

    return 0;
}
