/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>
#include<map>
#include<iostream>

using namespace std;

const int MAXN=210;

int first[MAXN],u[MAXN],v[MAXN],next[MAXN];
int d[MAXN][2],vis[MAXN],dup[MAXN][2];
int n,cntm;

void addedge(int x,int y)
{
    u[cntm]=x;v[cntm]=y;
    next[cntm]=first[x];
    first[x]=cntm++;
}

void dp(int x)
{
    if(vis[x]) return;

    vis[x]=1;

    d[x][0]=d[x][1]=0;

    bool isLeaf=true;

    for(int e=first[x];e!=-1;e=next[e])
    {
        isLeaf=false;
        dp(v[e]);

        if(d[v[e]][1]>d[v[e]][0])
        {
            d[x][0]+=d[v[e]][1];
            if(dup[v[e]][1])
                dup[x][0]=1;
        }
        else
        {
            d[x][0]+=d[v[e]][0];
            if(dup[v[e]][0])
                dup[x][0]=1;
        }
        if(d[v[e]][0]==d[v[e]][1])
            dup[x][0]=1;
        d[x][1]+=d[v[e]][0];
        if(dup[v[e]][0])
            dup[x][1]=1;
    }
    d[x][1]++;
    if(isLeaf)
    {
        dup[x][1]=dup[x][0]=0;
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif

    while(scanf("%d",&n)==1 && n)
    {
        memset(first,-1,sizeof(first));
        memset(vis,0,sizeof(vis));
        memset(dup,0,sizeof(dup));

        cntm=0;
        map<string,int> m;
        string a,b;

        int cnt=2;
        int pa,pb;

        cin>>a;

        m[a]=1;

        for(int i=0;i<n-1;i++)
        {
            cin>>a>>b;
            if(m.count(a)==0)
                m[a]=cnt++;
            if(m.count(b)==0)
                m[b]=cnt++;

            pa=m[a];
            pb=m[b];
            addedge(pb,pa);
        }
        dp(1);
        if(d[1][0]>d[1][1])
        {
            printf("%d %s\n",d[1][0],dup[1][0]==1?"No":"Yes");
        }
        else if(d[1][0]<d[1][1])
        {
            printf("%d %s\n",d[1][1],dup[1][1]==1?"No":"Yes");
        }
        else
        {
            printf("%d %s\n",d[1][1],"No");
        }

    }
    return 0;
}
