#include<iostream>
#include<cstring>
#include<queue>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

typedef struct
{
    int x, y, z;
    int step;
}Point;

using namespace std;

char maze[35][35][35];
int  vis[35][35][35];
int dx[6] = {1, 0, 0, -1, 0, 0};
int dy[6] = {0, 1, 0, 0, -1, 0};
int dz[6] = {0, 0, 1, 0, 0, -1};

int l, r, c;
Point st;
int nMin;
void bfs();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif

    int i, j, k;
    char ch;
    while(cin >> l >> r >> c)
    {
        if(l == 0 && r == 0 && c == 0)
        {
            break;
        }
        memset(vis, 0, sizeof(int) * 35 * 35  * 35);


        for(i = 0; i < l; i++)
        {
            for(j = 0; j < r; j++)
            {
                for(k = 0; k < c; k++)
                {
                    cin >> ch;
                    maze[i][j][k] = ch;
                    if(ch == 'S')
                    {
                        st.z = i;
                        st.x = k;
                        st.y = j;
                        st.step = 0;
                    }
                }
            }
        }
        nMin = -1;
        bfs();
        if(nMin == -1)
        {
            cout << "Trapped!" << endl;
        }
        else
        {
            cout << "Escaped in " << nMin << " minute(s)." << endl;
        }
    }
    return 0;
}

void bfs()
{
    Point temp;
    temp = st;
    queue<Point> q;
    q.push(temp);
    while( !q.empty())
    {
        temp = q.front();
        q.pop();
        if(temp.x < 0 || temp.y < 0 || temp.z < 0 || temp.z > l-1 || temp.y > r-1 || temp.x > c-1)
        {
            continue;
        }
        if(vis[temp.z][temp.y][temp.x] == 1)
        {
            continue;
        }
        vis[temp.z][temp.y][temp.x] = 1;
        if(maze[temp.z][temp.y][temp.x]  == 'E')
        {
            nMin = temp.step;
            return;
        }
        if(maze[temp.z][temp.y][temp.x]  == '#')
        {
            continue;
        }

        int i;
        for(i = 0; i < 6; i++)
        {
            temp.x += dx[i];
            temp.y += dy[i];
            temp.z += dz[i];
            temp.step++;
            q.push(temp);

            temp.x -= dx[i];
            temp.y -= dy[i];
            temp.z -= dz[i];
            temp.step--;

        }
    }
}
