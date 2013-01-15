/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cmath>
#include<queue>
#include<iostream>

using namespace std;

typedef long long LL;

struct node
{
    LL a;
    int size;
    int mod;
};

LL n;
int size;
int mod;

LL bfs()
{
    queue<node> q;
    queue<LL> ans;
    node tmp;
    size=0;
    mod=1;
    LL tn=n;
    while(tn)
    {
        size++;
        tn/=10;
        mod*=10;
    }

    tmp.a=0;
    tmp.size=0;
    tmp.mod=1;

    q.push(tmp);
    while(!q.empty())
    {
        tmp=q.front();q.pop();
        if(tmp.a*tmp.a%mod==n)
            ans.push(tmp.a);
        if(tmp.size==size)
        {
            continue;
        }

        for(int i=0;i<=9;i++)
        {
            tn=i*tmp.mod+tmp.a;
            node nt;
            nt.a=tn;
            nt.mod=tmp.mod*10;
            nt.size=tmp.size+1;
            if(tn*tn%nt.mod==n%nt.mod)
                q.push(nt);
        }
    }
    if(ans.empty())    return -1;
    LL mina=ans.front();
    ans.pop();
    while(!ans.empty())
    {
        tn=ans.front();
        ans.pop();
        if(mina>tn)
            mina=tn;
    }
    return mina;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif

    int T;
    cin>>T;
    while(T--)
    {
        cin>>n;
        LL ans=bfs();
        if(ans==(-1ll))
            puts("None");
        else
            cout<<ans<<endl;;
    }

    return 0;
}
