#include<iostream>
#include<cstring>
#include<algorithm>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

typedef struct
{
    int w, u, v;
}E;

E e[27*27];
int u[27];

bool comp(E a, E b);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int n, nSum;
    char s, c;
    while(cin >> n)
    {
        if(n == 0)
        {
            break;
        }
        memset(e, 0, sizeof(e));
        memset(u, 0, sizeof(u));
        int i, j, cnt, we, ne;
        for(i = 0,cnt = 0; i < n-1; i++)
        {
            cin >> s >> ne;
            for(j = 0; j < ne; j++)
            {
                cin >> c >> we;
                e[cnt].w = we;
                e[cnt].u = s-'A';
                e[cnt++].v = c-'A';
                u[s-'A']=u[c-'A']=1;
            }
        }
        sort(e, e+cnt, comp);
        nSum = e[0].w;
        u[e[0].u] = u[e[0].v]= -1;
        for(j = 1; j < cnt; j++)
        {
            for(i = 1; i < cnt; i++)
            {
                if(u[e[i].u]*u[e[i].v] < 0)
                {
                    nSum += e[i].w;
                    u[e[i].u] = u[e[i].v] = -1;
                    break;
                }
            }

        }
        cout << nSum << endl;
    }
    return 0;
}

bool comp(E a, E b)
{
    return a.w < b.w;
}
