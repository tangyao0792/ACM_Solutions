#include<stdio.h>

void main()
{
	double s[700];
	int num[700];
	double a[700], b[700];
	double x, y,temp;
	int i, j, k;
	int n;
	int index;
	int max;
	int noS;
	scanf("%d", &n);
	while(n != 0)
	{
		for(i = 0; i < n; i++)
		{
			scanf("%lf %lf", a +i, b+i);
			s[i] = 0;
			num[i] = 0;
		}
		noS = 0;
		max = 0;
		for(i = 0; i < n; i++)
		{
			x = a[i];
			y = b[i];
			
			index = 0;
			for(j = 0; j < n; j++)
			{
				s[j] = 0;
				num[j] = 0;
			}
			for(j = 0; j < n; j++)
			{
				if( j != i)
				{
					if( a[j] == x)
					{
						noS++;
					}
					else
					{
						temp = (b[j] - y)/(a[j] - x);

						for(k = 0; k < index; k++)
						{
							if(temp == s[k])
							{
								num[k]++;
								break;
							}
						}
						if( k == index)
						{
							s[index] = temp;
							num[index]++;
							index++;
						}
					}
				}
			}

			for(k = 0; k < index; k++)
			{
				if(max < num[k])
				{
					max = num[k];
				}
			}
			if(max < noS)
			{
				max = noS;
			}
		}

		printf("%d\n", max+1);
		scanf("%d", &n);
	}
}
