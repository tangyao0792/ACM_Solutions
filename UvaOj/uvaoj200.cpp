#include<iostream>
#include<cstring>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

char line[21];
char last[21];
int g[30][30];
int vis[30];
char arr[30];
int alphabet[26];
int cnt;
void topoSort();
void dfs(int cur);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int i;
    memset(last, 0, sizeof(last));
    memset(g, 0, sizeof(g));
    memset( vis, 0, sizeof(vis));
    memset(arr, 0, sizeof(arr));
    memset(alphabet, 0, sizeof( alphabet));
    while(cin >> line)
    {
        if(line[0] == '#')
        {
            break;
        }
        int nLen = strlen( line);
        for(i = 0; i < nLen; i++)
        {
            alphabet[ line[i] - 'A'] = 1;
        }
        nLen = strlen( last);
        for(i = 0; i < nLen; i++)
        {
            if( line[i] != last[i])
            {
                g[last[i]-'A'][line[i]-'A'] = 1;
                break;
            }
        }
        strcpy(last, line);
    }
    topoSort();
    for(i = 0; arr[i]; i++)
    {
        cout << arr[i];
    }
    cout << endl;
    return 0;
}

void dfs(int cur)
{
    int i;
    vis[cur] = 1;
    for(i = 0; i < 26; i++)
    {
        if(g[i][cur] && !vis[i])
        {
            dfs(i);
        }
    }
    arr[cnt++] = 'A'+cur;
}

void topoSort()
{
    int i;
    cnt = 0;
    for(i = 0; i < 26; i++)
    {
        if(alphabet[i])
        {
            if( !vis[i])
            {
                dfs(i);
            }
        }
    }
}
