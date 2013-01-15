#include<iostream>
#include<string.h>

#include<stdio.h>

using namespace std;

char maze[40][90];
int vis[40][90];
int dx[3] = { 0, 1, -1};
int dy[3] = { 0, 1, -1};

void dfs(int i, int j);

int main()
{
    freopen("in.txt", "r", stdin);
    int n;
    cin >> n;
    string st;
    getline( cin, st);
    int i, j, nLine;
    while(n--)
    {
        i = 0;
        memset(maze, 0, sizeof(char) * 40 * 90);
        memset(vis, 0, sizeof(int) * 40 * 90);
        while(true)
        {
            getline(cin, st);
            if(st[0] == '_')
            {
                break;
            }

            for(j = 0; j < st.size(); j++)
            {
                maze[i][j] = st[j];
            }
            i++;
        }
        nLine = i;

        for(i = 0; i < nLine; i++)
        {
            for(j = 0; maze[i][j] != 0; j++)
            {
                if(maze[i][j]== '*' && vis[i][j] == 0)
                {
                    dfs(i, j);
                }
            }
        }

        for(i = 0; i < nLine; i++)
        {
            cout << maze[i] << endl;
        }
        cout << st << endl;
    }

    return 0;
}

void dfs(int i, int j)
{

    if( i < 0 || j < 0 || i > 30 || j > 80)
    {
        return;
    }
    if(vis[i][j] == 1 || (maze[i][j] != '*' && maze[i][j] != ' '))
    {
        return;
    }
    maze[i][j] = '#';
    vis[i][j] = 1;
    int k, l;
    for(k = 0; k < 3; k++)
    {
        for(l = 0; l < 3; l++)
        {
            dfs(i+dx[k], j+dy[l]);
        }
    }
}
