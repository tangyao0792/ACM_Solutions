//����㷨

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
            if(nMin == -1 || nCurMin > nMin)//���ʱ��ȡ��ģ���Ϊֻ����Ĳ��ܱ�֤�������϶�ͨ��
            {
                nMin = nCurMin;
            }
            if(nMax == -1 || nCurMax > nMax)//�ʱ��ȥ���
            {
                nMax = nCurMax;
            }
        }
        cout << nMin << " " << nMax << endl;
    }
    return 0;
}
