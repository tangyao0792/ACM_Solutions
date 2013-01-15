#include<stdio.h>
#include<string.h>

void BubbleSort(int [], int);

void main()
{
	int n;
	char input[13];
	int len;
	int result[13];
	int num[5];
	int i;
	int flag;
	int a,b,c,d,e;
	scanf("%d %s", &n, input);
	while( n != 0)
	{
		flag = 0;
		len = strlen(input);
		for(i = 0; i < len; i++)
		{
			result[i] = input[i] -'A'+1;
		}
		BubbleSort(result,len);

		for(a = 0; a < len; a++)
		{
			for(b = 0; b < len; b++)
			{
				if( b != a)
				{
					for(c = 0; c <len; c++)
					{
						if(a != c && c != b)
						{
							for(d = 0; d <len; d++)
							{
								if(d != c && d!= b&& d != a)
								{
									for(e = 0; e <len; e++)
									{
										if( e!=d && e!= c && e!=b && e!=a)
										{
											if(result[a]
												-result[b]*result[b]
												+result[c]*result[c]*result[c]
												-result[d]*result[d]*result[d]*result[d]
												+result[e]*result[e]*result[e]*result[e]*result[e] == n)
											{
												num[0] = result[a];
												num[1] = result[b];
												num[2] = result[c];
												num[3] = result[d];
												num[4] = result[e];
												flag = 1;
											}
										}
									}

								}
							}
						}
					}
				}
			}
		}
		if(flag)
		{
			for( i = 0; i < 5; i++)
			{
				printf("%c",num[i] + 'A' -1);
			}
		}
		else
		{
			printf("no solution");
		}
		printf("\n");
		scanf("%d %s", &n, input);
	}
}

void BubbleSort(int a[],int n)
{
	int i,j;
	int temp;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n-i -1; j++)
		{
			if(a[j] > a[j+1])
			{
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}
}
