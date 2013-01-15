/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<iostream>
#include<cstring>
#include<set>

using namespace std;


int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int n;
    while(scanf("%d",&n)==1&&n)
    {
        set<string> all,loser;
        for(int i=0;i<n;i++)
        {
            string a, b;
            cin>>a>>b;
            all.insert(a);
            all.insert(b);
            loser.insert(b);
        }
        if(all.size()-loser.size()==1)
            cout<<"Yes"<<endl;
        else
            cout<<"No"<<endl;
    }
    return 0;
}
