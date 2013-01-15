#include<iostream>
#include<algorithm>
#include<string.h>

#ifndef ONLINE_JUDGE

	#include<stdio.h>

#endif

using namespace std;

int num[10010], hash[10010];

int main()
{

#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
#endif

	int n, q, i;
	int nCount = 0;
	while(cin >> n >> q)
	{
		if(n == 0 && q == 0)
		{
			break;
		}
		memset(num,0,n*sizeof(int));
		memset(hash,-1,10010*sizeof(int));

		nCount++;
		cout << "CASE# "<< nCount << ":" << endl;

		for(i = 0; i < n; i++)
		{
			cin >> num[i];
		}
		sort(num,num+n);
		for(i = 0; i < n; i++)
		{
			if(hash[num[i]] == -1)
			{
				hash[num[i]] = i + 1;
			}
		}
		for(i = 0; i < q; i++)
		{
			cin >> n;
			if(hash[n] != -1)
			{
				cout << n << " found at " << hash[n] <<endl;
			}
			else
			{
				cout << n << " not found" << endl;
			}
		}

	}
	return 0;
}
