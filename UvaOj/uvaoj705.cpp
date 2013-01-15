#include<iostream>
#include<cstring>

#ifndef ONLINE_JUDGE
    #include<stdio.h>
#endif

using namespace std;

int maze[230][230];
int vis[230][230];
int out, nMax, nLen;
int w, h;

void dfs(int i, int j);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif

    int nCountMaze = 0;
    int nCyc;
    while(cin >> w >> h)
    {
        if(w == 0 && h == 0)
        {
            break;
        }
        memset(maze, 0, sizeof(int) * 230 * 230);
        memset(vis, 0, sizeof(int) * 230 *230);

        nCountMaze++;
        nCyc = 0;
        nMax = 0;
        cout << "Maze #"<< nCountMaze <<":" << endl;


        int i, j;
        char c;
        for(i = 0; i < h; i++)
        {
            for(j = 0; j < w; j++)
            {
                cin >> c;
                if( c == '\\')
                {
                    maze[i*3][j*3] = 1;
                    maze[i*3+1][j*3+1] = 1;
                    maze[i*3+2][j*3+2] = 1;
                }
                else if( c == '/')
                {
                    maze[i*3][j*3+2] = 1;
                    maze[i*3+1][j*3+1] = 1;
                    maze[i*3+2][j*3] = 1;
                }
            }
        }

        for(i = 0; i < 3*h; i++)
        {
            for(j = 0; j < 3*w; j++)
            {
                if(maze[i][j] == 0 && vis[i][j] == 0)
                {
                    out = 0;
                    nLen = 0;
                    dfs(i, j);
                    if(out == 0)
                    {
                        nCyc++;
                        if( nLen > nMax)
                        {
                            nMax = nLen;
                        }
                    }
                }
            }
        }
        if(nCyc != 0)
        {
            cout << nCyc << " Cycles; the longest has length "<< nMax/3 <<"." << endl;
        }
        else
        {
            cout << "There are no cycles." << endl;
        }
        cout << endl;
    }
    return 0;
}

void dfs(int i, int j)
{
    if(vis[i][j] == 1 || maze[i][j] == 1)
    {
        return;
    }
    if(i < 0 || j < 0 || i > 3*h-1 || j > 3*w-1)
    {
        out = 1;
        return;
    }

    vis[i][j] = 1;
    nLen++;
    dfs(i+1, j);
    dfs(i, j+1);
    dfs(i-1, j);
    dfs(i, j-1);
}
