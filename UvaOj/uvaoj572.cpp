#include<iostream>
#include<string.h>

#ifndef ONLINE_JUDGE
	#include<stdio.h>
#endif

using namespace std;

char grid[110][110];

int nCount;

void traverseGrid(int i, int j);
int dir[3] = {1,0,-1};

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
#endif

	int r, c, i, j;
	while(cin >> r >> c)
	{
		if(r == 0 && c == 0)
		{
			break;
		}

		memset(grid,' ',110*110*sizeof(char));

		for(i = 1; i < r + 1; i++)
		{
			for(j = 1; j < c + 1; j++)
			{
				cin >> grid[i][j];
			}
		}

		nCount = 0;

		for(i = 1; i < r + 1; i++)
		{
			for(j = 1; j < c + 1; j++)
			{
				if(grid[i][j] == '@')
				{
					nCount++;
					traverseGrid(i,j);
				}
			}
		}
		cout << nCount << endl;

	}
	return 0;
}

void traverseGrid(int i, int j)
{
	int k,l;
	grid[i][j] = ' ';
	for(k = 0; k < 3; k++)
	{
		for(l = 0; l < 3; l++)
		{
			if(grid[i+dir[k]][j+dir[l]] == '@')
			{
				traverseGrid(i+dir[k], j+dir[l]);
			}
		}
	}
}
