#include<iostream>
#include<algorithm>
#include<cstring>

#define MAX 10000003

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;
typedef struct
{
    int a, b;
    int v;
}PlusN;
typedef struct
{
    int d, c;
    int v;
}SubN;

int headPl[MAX], nextPl[MAX];
int num[1010];
PlusN pl[1010*1010];
SubN su[1010*1010];

void insert_to_table_pl(int cnt);
void insert_to_table_su(int cnt);

int hash(int s);
int look_up_to(int s);
bool comp(SubN a, SubN b);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase, i, j, nFlag;
    while(cin >> nCase)
    {
        if(nCase == 0)
        {
            break;
        }
        memset(headPl, -1, sizeof(int) * MAX);
        memset(nextPl, -1, sizeof(int) * MAX);
        memset(pl, 0, sizeof(PlusN) * 1010*1010);
        memset(su, 0, sizeof(SubN) * 1010*1010);
        for(i = 0; i < nCase; i++)
        {
            cin >> num[i];
        }
        int cnt = 0;
        for(i = 0; i < nCase; i++)
        {
            for(j = 0; j < nCase; j++)
            {
                if(i != j )
                {
                    pl[cnt].a = num[i];
                    pl[cnt].b = num[j];
                    pl[cnt].v = num[i] + num[j];
                    insert_to_table_pl(cnt);

                    su[cnt].d = num[i];
                    su[cnt].c = num[j];
                    su[cnt].v = num[i] - num[j];
                    cnt++;
                }
            }
        }
        sort(su, su+cnt, comp);
        nFlag = 1;
        for(i = cnt-1; i > -1; i--)
        {
            if(look_up_to(i) == 1)
            {
                cout << su[i].d << endl;
                nFlag = 0;
                break;
            }
        }
        if(nFlag)
        {
            cout << "no solution" << endl;
        }
    }
    return 0;
}
bool comp(SubN a, SubN b)
{
    return a.d < b.d;
}

void insert_to_table_pl(int cnt)
{
    int h = hash(pl[cnt].v);
    int u = headPl[h];
    while(u != -1)
    {
        u = nextPl[u];
    }
    nextPl[cnt] = headPl[h];
    headPl[h] = cnt;
}

int hash(int s)
{
    int n, i;
    n = 0;
    while(s != 0)
    {
        i = s % 10;
        n = n * 10 + i * 31;
        s = s / 10;
    }
    n = n% MAX;
    if(n < 0)
    {
        n += MAX;
    }
    return n;
}
int look_up_to(int s)
{
    int h = hash(su[s].v);
    int u = headPl[h];
    while(u != -1)
    {
        if(pl[u].v == su[s].v
           && pl[u].a != su[s].c
           && pl[u].a != su[s].d
           && pl[u].b != su[s].c
           && pl[u].b != su[s].d)
        {
            return 1;
        }
        u = nextPl[u];
    }
    return 0;
}
