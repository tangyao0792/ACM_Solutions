#include<iostream>
#include<vector>
#include<queue>
#include<set>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;
typedef struct State
{
    int state[24];
    vector<int> step;
    bool operator < (const State &s) const
    {
        int i;
        for(i = 0; i < 24; i++)
        {
            if( this->state[i] < s.state[i])
            {
                return true;
            }
            else if( this->state[i] > s.state[i])
            {
                return false;
            }
        }
        return false;
    }
    bool operator == (const State &s) const
    {
        int i;
        for(i = 0; i < 24; i++)
        {
            if(this->state[i] != s.state[i])
            {
                return false;
            }
        }
        return true;
    }
}State;


int goal[24] = {0, 3, 4, 3, 0, 5, 6, 5, 0, 1, 2, 1,
                0, 7, 8, 7, 0, 9, 10, 9, 0, 1, 2, 1};
set<State> vis1;
set<State> vis2;
void bfs(int *start);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase;
    int start[24];
    cin >> nCase;
    while( nCase--)
    {
        int i;
        for(i = 0; i < 24; i++)
        {
            cin >> start[i];
        }
        bfs(start);
    }

    return 0;
}

void bfs(int *st)
{
    vis1.clear();
    vis2.clear();
    State start;
    int i;
    for(i = 0; i < 24; i++)
    {
        start.state[i] = st[i];
    }
    start.step.clear();
    queue<State> q;
    q.push(start);
    State tmp;
    while( !q.empty())              //ÕýÏò
    {
        tmp = q.front();
        q.pop();

        if(vis1.count(tmp) != 0 || tmp.step.size() > 8)
        {
            continue;
        }
        vis1.insert( tmp);
        for(i = 0; i < 24; i++)
        {
            if(tmp.state[i] != goal[i])
            {
                break;
            }
        }
        if(i == 24)
        {
            if(tmp.step.size() == 0)
            {
                cout << "PUZZLE ALREADY SOLVED" << endl;
                return;
            }
            for(i = 0; i < tmp.step.size(); i++)
            {
                cout << tmp.step[i];
            }
            cout << endl;
            return;
        }
        int a, b;
        State temp = tmp;

        temp.step.push_back(1);                 //×óË³Ê±Õë
        a = temp.state[10];
        b = temp.state[11];
        for(i = 11; i > 1; i--)
        {
            temp.state[i] = temp.state[i-2];
        }
        temp.state[0] = a;
        temp.state[1] = b;
        for(i = 0; i < 3; i++)
        {
            temp.state[21+i] = temp.state[9+i];
        }
        q.push(temp);

        temp = tmp;

        temp.step.push_back(3);                 //×óÄæÊ±Õë
        a = temp.state[0];
        b = temp.state[1];
        for(i = 0; i < 10; i++)
        {
            temp.state[i] = temp.state[i+2];
        }
        temp.state[10] = a;
        temp.state[11] = b;
        for(i = 0; i < 3; i++)
        {
            temp.state[21+i] = temp.state[9+i];
        }
        q.push(temp);

        temp = tmp;
        temp.step.push_back(2);                 //ÓÒË³Ê±Õë

        a = temp.state[12];
        b = temp.state[13];
        for(i = 12; i < 22; i++)
        {
            temp.state[i] = temp.state[i+2];
        }
        temp.state[22] = a;
        temp.state[23] = b;
        for(i = 0; i < 3; i++)
        {
            temp.state[9+i] = temp.state[21+i];
        }
        q.push(temp);

        temp = tmp;
        temp.step.push_back(4);                 //ÓÒÄæÊ±Õë
        for(i = 23; i > 10; i--)
        {
            temp.state[i] = temp.state[i-2];
        }
        for(i = 0; i < 3; i++)
        {
            temp.state[9+i] = temp.state[21+i];
        }
        q.push(temp);

    }


    for(i = 0; i < 24; i++)
    {
        start.state[i] = goal[i];
    }
    start.step.clear();
    q.push(start);


    while( !q.empty())
    {
        tmp = q.front();
        q.pop();
        if(vis1.count(tmp) != 0)
        {
            set<State>::iterator it;
            for(it = vis1.begin(); it != vis1.end(); it++)
            {
                if( *it == tmp)
                {
                    break;
                }
            }
            if( (*it).step.size() + tmp.step.size() > 16)
            {

            }
            else
            {
                for(i = 0; i < (*it).step.size(); i++)
                {
                    cout << (*it).step[i];
                }
                for(i = tmp.step.size()-1; i > -1; i--)
                {
                    cout << tmp.step[i];
                }
                cout << endl;
                return;
            }
        }
        if(vis2.count(tmp) != 0 || tmp.step.size() > 8)
        {
            continue;
        }
        vis2.insert( tmp);
        int a, b;
        State temp = tmp;

        temp.step.push_back(3);                 //×óË³Ê±Õë
        a = temp.state[10];
        b = temp.state[11];
        for(i = 11; i > 1; i--)
        {
            temp.state[i] = temp.state[i-2];
        }
        temp.state[0] = a;
        temp.state[1] = b;
        for(i = 0; i < 3; i++)
        {
            temp.state[21+i] = temp.state[9+i];
        }
        q.push(temp);

        temp = tmp;

        temp.step.push_back(1);                 //×óÄæÊ±Õë
        a = temp.state[0];
        b = temp.state[1];
        for(i = 0; i < 10; i++)
        {
            temp.state[i] = temp.state[i+2];
        }
        temp.state[10] = a;
        temp.state[11] = b;
        for(i = 0; i < 3; i++)
        {
            temp.state[21+i] = temp.state[9+i];
        }
        q.push(temp);

        temp = tmp;
        temp.step.push_back(4);                 //ÓÒË³Ê±Õë

        a = temp.state[12];
        b = temp.state[13];
        for(i = 12; i < 22; i++)
        {
            temp.state[i] = temp.state[i+2];
        }
        temp.state[22] = a;
        temp.state[23] = b;
        for(i = 0; i < 3; i++)
        {
            temp.state[9+i] = temp.state[21+i];
        }
        q.push(temp);

        temp = tmp;
        temp.step.push_back(2);                 //ÓÒÄæÊ±Õë
        for(i = 23; i > 10; i--)
        {
            temp.state[i] = temp.state[i-2];
        }
        for(i = 0; i < 3; i++)
        {
            temp.state[9+i] = temp.state[21+i];
        }
        q.push(temp);


    }

    cout << "NO SOLUTION WAS FOUND IN 16 STEPS" << endl;
}
