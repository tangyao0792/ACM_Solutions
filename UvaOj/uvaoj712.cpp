#include<iostream>

#ifndef ONLINE_JUDGE
	#include<stdio.h>
#endif

using namespace std;

int main()
{

#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
#endif

	char v[130];
	int vva[7];
	char p[7];
	char input[3];
	int n, m, i, j, len, l, r;
	int nCount = 0;
	while(cin >> n)
	{
		if(n == 0)
		{
			break;
		}
		nCount++;
		cout << "S-Tree #" << nCount << ":" << endl;

		for(i = 0; i < n; i++)
		{
			cin >> input;
			vva[i] = input[1] - '0'-1;
		}
		len = 1<<n;

		for(i = 0; i < len; i++)
		{
			cin >> v[i];
		}
		cin >> m;
		for(i = 0; i < m; i++)
		{
			l = 0;
			r = len -1;
			for(j = 0; j < n; j++)
			{
				cin >> p[j];
			}
			for(j = 0; j < n; j++)
			{
				if( p[vva[j]] == '0')
				{
					r = (l + r) / 2;
				}
				else
				{
					l = (l + r) / 2+1;
				}
			}
			cout << v[l];
		}
		cout << endl << endl;

	}
	return 0;
}
