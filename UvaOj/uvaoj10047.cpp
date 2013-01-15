#include<iostream>
#include<cstring>
#include<queue>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

typedef struct
{
    int x, y, c;        //1´ú±íÂÌÉ«
    int d;              //0123UDLR
    int step;
}Point;

char maze[30][30];
int vis[30][30][5][4];
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
int sx, sy, tx, ty;
int minStep;
int m, n;

void bfs();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    int i, j;
    int nCase = 0;
    while(cin >> m >> n)
    {
        if(m == 0 && n == 0)
        {
            break;
        }
        nCase++;
        if(nCase != 1)
        {
            cout << endl;
        }
        cout << "Case #" << nCase << endl;
        memset(maze, 0, sizeof(char) * 30 * 30);
        memset(vis, 0, sizeof(int) * 30 * 30 * 5*4);
        for(i = 0; i < m; i++)
        {
            for(j = 0; j < n; j++)
            {
                cin >> maze[i][j];
                if( maze[i][j] == 'S')
                {
                    sx = i;
                    sy = j;
                }
                if(maze[i][j] == 'T')
                {
                    tx = i;
                    ty = j;
                }
            }
        }
        minStep = -1;
        bfs();

        if(minStep == -1)
        {
            cout << "destination not reachable" << endl;
        }
        else
        {
            cout << "minimum time = " << minStep <<" sec" <<endl;
        }
    }
    return 0;
}

void bfs()
{
    Point temp;
    int i;
    temp.x = sx;
    temp.y = sy;
    temp.c = 1;
    temp.step = 0;
    temp.d = 0;

    queue<Point> q;
    q.push(temp);

    while( !q.empty())
    {
        temp = q.front();
        q.pop();

        if(vis[temp.x][temp.y][temp.c][temp.d] == 1)
        {
            continue;
        }
        vis[temp.x][temp.y][temp.c][temp.d] = 1;
        if(maze[temp.x][temp.y] == 'T' && temp.c == 1 )
        {
            minStep = temp.step;
            return;
        }
        temp.step++;
        for(i = -1; i < 2; i++)
        {
            if(i == 0)
            {
                temp.x += dx[temp.d];
                temp.y += dy[temp.d];
                int tmpc = temp.c;
                temp.c = (tmpc + 1) % 5;
                if(temp.x < m && temp.x > -1
                   && temp.y < n && temp.y > -1
                   && maze[temp.x][temp.y] != '#')
                {
                    q.push(temp);
                }
                temp.c = tmpc;
                temp.x -= dx[temp.d];
                temp.y -= dy[temp.d];
            }
            else
            {
                int tmpd = temp.d;
                temp.d = (tmpd + 4 + i) % 4;
                q.push(temp);
                temp.d = tmpd;
            }
        }
    }
}
