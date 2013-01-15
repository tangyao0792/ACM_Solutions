#include<iostream>

#include<stdio.h>

using namespace std;

char img[60][60];
int w, h;
int dot[7];
int nDot;
int dir[3] = {1, 0, -1};

void dfsDice(int i, int j);           //找到筛子后dfs这个筛子
void dfsDot(int i, int j);         //dfs找点数

int main()
{
    freopen("in.txt", "r", stdin);
    int i, j;
    int nCount = 0;

    while(cin >> w >> h)
    {
        if(w == 0 && h == 0)
        {
            break;
        }
        for(i = 0; i < 60; i++)
        {
            for(j = 0; j < 60; j++)
            {
                img[i][j] = '.';
            }
        }
        getchar();
        nCount++;
        cout << "Throw " << nCount << endl;

        for( i = 0; i < 7; i++)
        {
            dot[i] = 0;
        }
        string st;
        for(i = 0; i < h; i++)
        {
            getline(cin, st);
            for(j = 0; j < st.size(); j++)
            {
                img[i+1][j+1] = st[j];
            }
        }

        for(i = 1; i < h+1; i++)
        {
            for(j = 1; j < w+1; j++)
            {
                if(img[i][j] != '.')
                {
                    nDot = 0;
                    dfsDice(i, j);
                    dot[nDot]++;
                }
            }
        }
        int nc = 0;
        for(i = 1; i < 7; i++)
        {
            for(j = 0; j < dot[i]; j++)
            {
                if(nc)
                {
                    cout << " ";

                }
                nc++;
                cout << i;
            }
        }
        cout << endl << endl;
    }
    return 0;
}
void dfsDot(int i, int j)
{
    if(img[i][j] == '.' || img[i][j] != 'X')
    {
        return;
    }
    img[i][j] = '.';
    dfsDot(i+1,j);
    dfsDot(i,j+1);
    dfsDot(i,j-1);
    dfsDot(i-1,j);
}

void dfsDice(int i, int j)
{
    if(img[i][j] == '.' )
    {
        return ;
    }
    if(img[i][j] == 'X')
    {
        nDot++;
        dfsDot(i, j);
    }
    img[i][j] = '.';
    dfsDice(i+1,j);
    dfsDice(i,j+1);
    dfsDice(i,j-1);
    dfsDice(i-1,j);


}
