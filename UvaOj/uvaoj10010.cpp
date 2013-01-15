#include<iostream>
#include<cstring>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

char grid[55][55];
int n, m;
char word[25];
int x, y;

void find();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase, i, j, k, num;
    char c = 32;
    cin >> nCase;
    for(i = 0; i < nCase; i++)
    {
        if(i != 0)
        {
            cout << endl;
        }
        cin >> m >> n;
        for(j = 0; j < m; j++)
        {
            for(k = 0; k < n; k++)
            {
                cin >> grid[j][k];
                grid[j][k] = grid[j][k] | c;
            }
        }
        cin >> num;
        for(j = 0; j < num; j++)
        {
            cin >> word;
            find();
            cout << x +1<< " " << y+1 << endl;
        }

    }
    return 0;
}

void find()
{
    int i, j, k;
    int nLen = strlen(word);
    for(i = 0; i < nLen; i++)
    {
        word[i] = word[i] | 32;
    }
    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        {
            for(k = 0; k < nLen; k++)
            {
                if( word[k] != grid[i][j+k] || j+k > n)
                {
                    break;
                }
            }
            if(k == nLen)
            {
                x = i;
                y = j;
                return;
            }
            for(k = 0; k < nLen; k++)
            {
                if(word[k] != grid[i+k][j] || i+k > m)
                {
                    break;
                }
            }
            if(k == nLen)
            {
                x = i;
                y = j;
                return;
            }
            for(k = 0; k < nLen; k++)
            {
                if(word[k] != grid[i+k][j+k]|| j+k > n
                    || i+k > m)
                {
                    break;
                }
            }
            if(k == nLen)
            {
                x = i;
                y = j;
                return;
            }
            for(k = 0; k < nLen; k++)
            {
                if( word[k] != grid[i][j-k] || j-k < 0)
                {
                    break;
                }
            }
            if(k == nLen)
            {
                x = i;
                y = j;
                return;
            }
            for(k = 0; k < nLen; k++)
            {
                if(word[k] != grid[i-k][j]||i-k<0)
                {
                    break;
                }
            }
            if(k == nLen)
            {
                x = i;
                y = j;
                return;
            }
            for(k = 0; k < nLen; k++)
            {
                if(word[k] != grid[i-k][j-k]||i-k<0||j-k<0)
                {
                    break;
                }
            }
            if(k == nLen)
            {
                x = i;
                y = j;
                return;
            }
        }
    }
}
