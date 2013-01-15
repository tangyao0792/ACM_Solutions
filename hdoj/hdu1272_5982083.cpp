/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>
#include<iostream>
#include<set>

using namespace std;

//struct Edge {
//    int a, b;
//
//    Edge(int _a, int _b) : a(_a), b(_b) {}
//
//    bool operator < (const struct Edge &t) const {
//        if(a == t.a)
//            return b < t.b;
//        else
//            return a < t.a;
//    }
//    bool operator == (const struct Edge &t) const {
//       return ((a == t.a) && (b == t.b));
//    }
//};

const int MAXN=100010;

int p[MAXN];
int vis[MAXN];

int find(int x){return p[x]==-1?x:(p[x]=find(p[x]));}

bool unionset(int x,int y)
{
    x=find(x);
    y=find(y);
    if(x!=y)
    {
        p[x]=y;
        return true;
    }
    return false;
}

void swap(int &a,int &b)
{
    if(a>b)
    {
        int tmp=a;
        a=b;
        b=tmp;
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r",stdin);
#endif

    int a=0,b=0;

    while(scanf("%d %d",&a,&b)==2)
    {
        if(a==-1 && b==-1)  break;
        if(a==0 && b==0)
        {
            printf("Yes\n");
            continue;
        }
//        set<struct Edge> s;
        bool flag=true;

        memset(p,-1,sizeof(p));
        memset(vis,0,sizeof(vis));


        vis[a]=vis[b]=1;
        swap(a,b);
//        struct Edge e(a,b);
        if(flag )
        {
          //  s.insert(e);
            if(!unionset(a,b))
            {
                flag=false;
            }
        }
        while(scanf("%d %d",&a,&b)==2)
        {
            if(a==0 && b==0)    break;
            //if(a==b)    continue;
            vis[a]=vis[b]=1;
            swap(a,b);
           // struct Edge e(a,b);
            if(flag )
            {
              //  s.insert(e);
                if(!unionset(a,b))
                {
                    flag=false;
                }
            }
        }

        int tmp=-1;
        for(int k=1;k<=100000;k++)
        {
            if(vis[k])
            {
                tmp=find(k);
                break;
            }
        }

        for(int i=1;i<MAXN && flag;i++)
        {
            if(vis[i])
            {
                int t=find(i);
                if(tmp!=t)
                {
                    flag=false;
                }
            }
        }
        if(flag)
            printf("Yes\n");
        else
            printf("No\n");
    }



    return 0;
}
