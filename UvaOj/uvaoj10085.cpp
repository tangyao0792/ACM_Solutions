#include<iostream>
#include<queue>
#include<set>
#include<vector>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

typedef struct State
{
    int s[3][3];
    vector<char> step;

    bool operator < (const State &b) const
    {
        int i, j;
        for(i = 0; i < 3; i++)
        {
            for(j = 0; j < 3; j++)
            {
                if((*this).s[i][j] > b.s[i][j] )
                {
                    return false;
                }
                else if( (*this).s[i][j] < b.s[i][j])
                {
                    return true;
                }
            }
        }
        return false;
    }
}State;

State iniS, tarS;
int dx[4] = {-1, 1, 0, 0};             //ÐÐ
int dy[4] = {0, 0, -1, 1};
char dir[5] = "UDLR";

void bfs();
void swap(int &a, int &b);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase, i, j, k;
    cin >> nCase;
    for(i = 0; i < nCase; i++)
    {
        cout << "Puzzle #" << i+1 << endl;
        iniS.step.clear();
        tarS.step.clear();
        for(j = 0; j < 3; j++)
        {
            for(k = 0; k < 3; k++)
            {
                cin >> iniS.s[j][k];
            }
        }
        bfs();
        for(j = 0; j < 3; j++)
        {
            for(k = 0; k < 3; k++)
            {
                if(k != 0)
                {
                    cout << " ";
                }
                cout << tarS.s[j][k];
            }
            cout << endl;
        }

        vector<char>::iterator it;
        for(it = tarS.step.begin(); it != tarS.step.end(); it++)
        {
            cout << *it;
        }
        cout << endl << endl;
    }
    return 0;
}

void bfs()
{
    queue<State> q;
    set<State> vis;
    int i, j, x, y, newx, newy;
    State temp;
    q.push(iniS);

    while( !q.empty())
    {
        iniS = q.front();
        q.pop();
        if(vis.count(iniS) != 0)
        {
            continue;
        }
        vis.insert(iniS);
        tarS = iniS;

        for(i = 0; i < 3; i++)
        {
            for(j = 0 ; j < 3; j++)
            {
                if(iniS.s[i][j] == 0)
                {
                    x = i;
                    y = j;
                    break;
                }
            }
        }

        for(i = 0; i < 4; i++)
        {
            temp = iniS;
            newx = x + dx[i];
            newy = y + dy[i];
            if(newx < 0 || newy < 0 || newx > 2 || newy > 2)
            {
                continue;
            }
            swap(temp.s[x][y], temp.s[newx][newy]);
            temp.step.insert(temp.step.end(), dir[i]);

            q.push(temp);
        }
    }

}

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}
