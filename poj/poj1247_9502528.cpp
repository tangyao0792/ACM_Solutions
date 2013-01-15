#include<stdio.h>

void main()
{
	int n;
	int sam, ella;
	int pos[30];
	int i, j;
	scanf("%d", &n);
	while(n != 0)
	{
		for( i = 0; i < n; i++)
		{
			scanf("%d", pos + i);
		}
		sam = 0;
		ella = 0;
		for(i = 0; i < n; i++)
		{
			for(j = 0; j < i+1; j++)
			{
				sam += pos[j];
			}
			for(j = i+1; j < n; j++)
			{
				ella += pos[j];
			}

			if( sam == ella)
			{
				printf("Sam stops at position %d and Ella stops at position %d.\n", i+1, i+2);
				break;
			}
			sam = 0;
			ella = 0;
		}
		if( i == n)
		{
			printf("No equal partitioning.\n");
		}
		scanf("%d", &n);

	}
}
