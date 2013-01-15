#include<iostream>
#include<cstring>
#include<algorithm>
#include<string>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

string frag[300];
int vis[300];
int num;

bool comp(string a, string b);
int findS(string file);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase, i;
    cin >> nCase;
    getline(cin, frag[0]);
    getline(cin, frag[0]);
    while( nCase--)
    {

        for(i = 0; getline(cin, frag[i]); i++)
        {
            if(frag[i].size() == 0)
            {
                break;
            }
        }
        num = i;
        sort(frag, frag+i, comp);
        int len = frag[0].size();
        for(i = 0; i < num/2+1 && len == frag[i].size(); i++)
        {
            string f = frag[i] + frag[num-1];
            if( findS(f) == 1)
            {
                cout << f << endl;
                break;
            }
            f = frag[num-1] + frag[i];
            if( findS(f) == 1)
            {
                cout << f << endl;
                break;
            }
        }
        if( nCase != 0)
        {
            cout << endl;
        }
    }
    return 0;
}

int findS(string f)
{
    memset(vis, 0, sizeof(int) * 300);
    int nFlag;
    int i, j;
    for(i = 0; i < num; i++)
    {
        if(vis[i] == 1)
        {
            continue;
        }
        vis[i] = 1;
        nFlag = 0;
        for(j = 0; j < num; j++)
        {
            if(i != j && vis[j] == 0
               && (frag[j] + frag[i] == f ||frag[i] + frag[j] == f))
            {
                vis[j] = 1;
                nFlag = 1;
                break;
            }
        }
        if( nFlag == 0)
        {
            return 0;
        }
    }
    return 1;
}
bool comp(string a, string b)
{
    return a.size() > b.size();
}
