#include<iostream>
#include<cstring>

#ifndef ONLINE_JUDGE
    #include<stdio.h>
#endif

using namespace std;
int a, b, c, d;
int closestD;
long long minSum, sum;
int dir[3] = {-1, 0, 1};
int vis[201][201];

void dfs(int i, int j, int k);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int n, i;
    cin >> n;
    for(i = 0; i < n; i++)
    {
        memset(vis, 0, sizeof(int) * 201 * 201);
        cin >> a >> b >> c >> d;
        closestD = 0;
        sum = 0;
        minSum = -1;
        dfs(0, 0, c);

        cout << minSum << " " << closestD << endl;
    }
    return 0;
}

void dfs(int i, int j, int k)
{
    if(i > a || j > b || k > c || i < 0 || j < 0 || k < 0 )
    {
        return;
    }
    int array[3] = {i, j, k};
    int arr[3] = {a, b, c};
    int l, m;
    for(l = 0; l < 3; l++)
    {
        if(array[l] == d)
        {
            if(closestD == d)
            {
                if(minSum > sum || minSum == -1)
                {
                    minSum = sum;
                }
            }
            else
            {
                closestD = d;
                minSum = sum;
            }
        }
        else if(array[l] < d)
        {
            if(closestD == d)
            {
            }
            else if(array[l] == closestD && (minSum > sum || minSum == -1))
            {
                minSum = sum;
            }
            else if(array[l] > closestD)
            {
                closestD = array[l];
                minSum = sum;
            }
        }
    }

    int nMin;
    for(l = 0; l < 3; l++)              //a[l]为倒出杯
    {
        for(m = 0; m < 3; m++)          //a[m]为倒入杯
        {
            if(array[l] != 0 && array[m] != arr[m])
            {
                nMin = arr[m] - array[m];
                if(nMin > array[l])
                {
                    nMin = array[l];
                }

                array[l] -= nMin;
                array[m] += nMin;
                sum += nMin;
                if(vis[array[1]][array[2]] == 0)
                {
                    vis[array[1]][array[2]] = 1;            //vis一定只能在这里判断，
                    dfs(array[0], array[1], array[2]);      //因为不同的路都可能到达目的，
                    vis[array[1]][array[2]] = 0;            //不一定是最先到的sum最小
                }
                array[l] += nMin;
                array[m] -= nMin;
                sum -= nMin;


            }
        }
    }

}

/*
    不能用bfs，因为最先找到的不一定是sum最小的

*/


//#include<iostream>
//#include<queue>
//#include<cstring>
//
//#ifndef ONLINE_JUDGE
//    #include<stdio.h>
//#endif
//
//using namespace std;
//
//typedef struct
//{
//    int cup[3];
//    int step;
//}state;
//
//int a, b, c, d;
//int closestD;
//int nStep;
//int vis[201][201][201];
//void bfs();
//
//int main()
//{
//#ifndef ONLINE_JUDGE
//    freopen("in.txt", "r", stdin);
//#endif
//
//    int n, i;
//    cin >> n;
//    for(i = 0; i < n; i++)
//    {
//        cin >> a >> b >> c >> d;
//        closestD = 0;
//        bfs();
//        cout << nStep << " " << closestD << endl;
//    }
//    return 0;
//}
//
//void bfs()
//{
//
//    memset(vis, 0, sizeof(int) * (a+1) * (b+1) * (c+1));
//    queue<state> q;
//    state temp;
//    int arr[3];
//    int i, j, nMin;
//    arr[0] = a; arr[1] = b; arr[2] = c;
//    temp.cup[0] = 0;
//    temp.cup[1] = 0;
//    temp.cup[2] = c;
//    temp.step = 0;
//    q.push(temp);
//
//
//    while( !q.empty())
//    {
//        temp = q.front();
//        q.pop();
//
//        if(vis[temp.cup[0]][temp.cup[1]][temp.cup[2]] == 1)
//        {
//            continue;
//        }
//        vis[temp.cup[0]][temp.cup[1]][temp.cup[2]] = 1;
//        for(i = 0; i < 3; i++)
//        {
//            if(temp.cup[i] == d)
//            {
//                closestD = d;
//                nStep = temp.step;
//                return;
//            }
//            else if( temp.cup[i] < d && temp.cup[i] > closestD)
//            {
//                closestD = temp.cup[i];
//                nStep = temp.step;
//            }
//        }
//
//        for(i = 0; i < 3; i++)              //cup[i]为倒出杯
//        {
//            for(j = 0; j < 3; j++)          //cup[j]为倒入杯
//            {
//                if(temp.cup[i] != 0 && temp.cup[j] != arr[j])
//                {
//                    nMin = arr[j] - temp.cup[j];
//                    if(nMin > temp.cup[i])
//                    {
//                        nMin = temp.cup[i];
//                    }
//
//                    temp.cup[i] -= nMin;
//                    temp.cup[j] += nMin;
//                    temp.step += nMin;
//
//                    q.push(temp);
//
//                    temp.cup[i] += nMin;
//                    temp.cup[j] -= nMin;
//                    temp.step -= nMin;
//                }
//            }
//        }
//
//    }
//
//}
