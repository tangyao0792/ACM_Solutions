#include<cstdio>
#include<cstring>
#include<iostream>
#include<map>
#include<vector>

using namespace std;

const int INF=1<<28;
const int MAXM=15;
const int MAXN=110;
const int MAXT=1010;

int n,m;
vector<int> v[MAXM];
int dp[MAXT*MAXN];
int w[MAXN];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif

    map<string,int> color;

    while(cin>>m>>n)
    {
        if(!n && !m)    break;
        color.clear();
        string a;
        for(int i=1;i<=m;i++)
        {
            cin>>a;
            color[a]=i;
            v[i].clear();
        }
        for(int i=0;i<n;i++)
        {
            int t;
            cin>>t>>a;
            int p=color[a];
            v[p].push_back(t);
        }

        int ans=0;
        for(int i=1;i<=m;i++)
        {
            int s=v[i].size();

            if(!s)  continue;

            int V=0;
            for(int j=1;j<=s;j++)
            {
                w[j]=v[i][j-1];
                V+=w[j];
            }

            memset(dp,0,sizeof(dp));
            dp[0]=1;

            for(int j=1;j<=s;j++)
                for(int k=V;k>=w[j];k--)
                    if(dp[k-w[j]])
                        dp[k]=1;

            int nMin=INF;
            for(int j=0;j<=V;j++)
                if(dp[j])
                    nMin=min(nMin,max(j,V-j));

            ans+=nMin;
        }
        cout<<ans<<endl;
    }

    return 0;
}
