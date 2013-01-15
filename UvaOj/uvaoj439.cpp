#include<iostream>
#include<queue>
#include<cstring>
#include<string>
#include<sstream>

#ifndef ONLINE_JUDGE
    #include<stdio.h>
#endif

typedef struct
{
    int x, y;
    int step;
}point;

using namespace std;
int vis[8][8];
point start, end;
int dx[8] = {-2,-1,1,2,-2,-1,1,2};
int dy[8] = {1,2,2,1,-1,-2,-2,-1};

void bfs();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif

    string input;
    while( getline(cin, input))
    {
        char a1, b1;
        int a2, b2;
        stringstream ss(input);
        ss >> a1 >> a2 >> b1 >> b2;

        start.x = a1-'a';
        start.y = a2-1;
        start.step = 0;
        end.x = b1 - 'a';
        end.y = b2-1;
        end.step = 0;
        bfs();
        cout << "To get from "
        <<a1<<a2<<" to "<<b1<<b2
        <<" takes "<<end.step
        <<" knight moves."<<endl;

    }
    return 0;
}

void bfs()
{
    queue<point> q;
    int i;
    point temp = start;
    q.push(temp);
    memset(vis, 0, sizeof(int) * 8 * 8 );

    while( !q.empty())
    {
        temp = q.front();
        q.pop();

        if(temp.x > 7 || temp.x < 0 || temp.y > 7 || temp.y < 0 || vis[temp.x][temp.y] == 1)
        {
            continue;
        }
        vis[temp.x][temp.y] = 1;

        if(temp.x == end.x && temp.y == end.y)
        {
            end.step = temp.step;
            return;
        }

        for(i = 0; i < 8; i++)
        {
            temp.x += dx[i];
            temp.y += dy[i];
            temp.step++;

            q.push(temp);

            temp.x -= dx[i];
            temp.y -= dy[i];
            temp.step--;
        }
    }
}
