#include <stdio.h>
void main()
{
	int count;
	double dest,sum;
	while( scanf("%lf" ,&dest) != EOF)
	{
		count = 0;
		sum = 0;
		while(sum < dest)
		{
			count++;
			sum += 1.0/(count+1);
			if( sum > dest )
			{
				printf("%d card(s)\n",count);
			}
		}
	}
}
