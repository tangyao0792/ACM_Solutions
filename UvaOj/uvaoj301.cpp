#include<iostream>
#include<cstring>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

int cap;        //火车容量
int dest;       //终点
int ord;        //票务请求量
int nMax;

int order[25][3];       //[0]记起点，【1】终点，【2】数量
int vis[25];            //表示当前站的人数

void dfs(int cur, int sum);     //cur当前处理的order、sum为当前乘客数
int is_ok(int cur);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int i;
    while( cin >> cap >> dest >> ord)
    {
        if(cap == 0 && dest == 0 && ord == 0)
        {
            break;
        }
        memset(vis, 0, sizeof(int) * 25);
        for(i = 0; i < ord; i++)
        {
            cin >> order[i][0] >> order[i][1] >> order[i][2];
        }
        nMax = 0;
        dfs(0, 0);
        cout << nMax << endl;
    }
    return 0;
}


int is_ok(int cur)      //vis[cur] == 1是否可以
{
    int i;
    for(i = order[cur][0]; i < order[cur][1]; i++)
    {
        if(vis[i] + order[cur][2] > cap)
        {
            return 0;
        }
    }
    return 1;
}

void dfs(int cur, int sum)
{
    if(cur == ord)
    {
        if(sum > nMax)
        {
            nMax = sum;
        }
        return;
    }
    int i;
    if(is_ok(cur) == 1)
    {
        for(i = order[cur][0] ; i < order[cur][1]; i++)
        {
            vis[i] += order[cur][2];
        }
        dfs(cur+1, sum + order[cur][2] * (order[cur][1] - order[cur][0]));

        for(i = order[cur][0]; i < order[cur][1]; i++)
        {
            vis[i] -= order[cur][2];
        }
    }
    dfs(cur+1, sum);
}
