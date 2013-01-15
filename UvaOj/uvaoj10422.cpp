#include<iostream>
#include<cstring>
#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

char maze[5][5];
char *target = "111110111100 110000100000";
int nMin;
int dx[8] = {-2, -2, -1,  1,  2,  2,  1,  -1};
int dy[8] = {-1,  1,  2,  2,  1, -1, -2,  -2};

void dfs(int x, int y, int cur);
void swapc(char &a, char &b);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase;
    int i, j;
    int x, y;
    cin >> nCase;
    string line;getline(cin, line);
    while( nCase--)
    {

        for(i = 0; i < 5; i++)
        {
            getline(cin,line);
            for(j = 0; j < 5; j++)
            {
                maze[i][j] = line[j];
                if(maze[i][j] == ' ')
                {
                    x = i;
                    y = j;
                }
            }
        }
        nMin = 11;
        dfs(x, y, 0);
        if(nMin > 10)
        {
            cout << "Unsolvable in less than 11 move(s)." << endl;
        }
        else
        {
            cout << "Solvable in " << nMin << " move(s)." << endl;
        }
    }
    return 0;
}

void dfs(int x, int y, int cur)
{
    if(cur > 10)
    {
        return;
    }

    if(memcmp(maze,target, sizeof(maze)) == 0 && cur < nMin)
    {
        nMin = cur;
        return;
    }


    int i;
    int newx, newy;
    for(i = 0; i < 8; i++)
    {
        newx = x+dx[i];
        newy = y+dy[i];
        if(newx > -1 && newx < 5 && newy > -1 && newy < 5)
        {
            swap(maze[newx][newy], maze[x][y]);
            dfs(newx, newy, cur+1);
            swap(maze[newx][newy], maze[x][y]);
        }

    }
}

void swapc(char &a, char &b)
{
    char temp = a;
    a = b;
    b = temp;
}
