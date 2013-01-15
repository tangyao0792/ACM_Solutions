//鬼魂算法

#include<iostream>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase, nLen, nMin, nMax, nCurMin, nCurMax;
    int pos, num, i;
    cin >> nCase;

    while(nCase--)
    {
        cin >> nLen >> num;
        nMin = nMax = -1;
        for(i = 0; i < num; i++)
        {
            cin >> pos;
            nCurMin = nLen - pos;
            if(pos < nCurMin)
            {
                nCurMax = nCurMin;
                nCurMin = pos;
            }
            else
            {
                nCurMax = pos;
            }
            if(nMin == -1 || nCurMin > nMin)//最短时间取最长的，因为只有最长的才能保证所有蚂蚁都通过
            {
                nMin = nCurMin;
            }
            if(nMax == -1 || nCurMax > nMax)//最长时间去最长的
            {
                nMax = nCurMax;
            }
        }
        cout << nMin << " " << nMax << endl;
    }
    return 0;
}
