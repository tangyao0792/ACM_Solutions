#include<stdio.h>

void main()
{
	int number_A, number_B, temp;
	int max_length;
	int step;
	int num;
	int length;
	int flag;

	while(scanf("%d %d", &number_A, &number_B) != EOF )
	{
		flag = 0;
		if(number_A > number_B)
		{
			temp = number_A;
			number_A = number_B;
			number_B = temp;
			flag = 1;
		}
		max_length = 0;
		for(step = number_A; step < number_B+1; step++)
		{
			num = step;
			length = 1;
			while(num != 1)
			{
				if(num % 2 == 1)
				{
					num = 3*num+1;
				}
				else
				{
					num /= 2;
				}
				length++;
			}
			if(max_length < length)
			{
				max_length = length;
			}
		}
		if(flag == 1)
		{
			printf("%d %d %d\n", number_B, number_A, max_length);			
		}
		else
		{
			printf("%d %d %d\n", number_A, number_B, max_length);			
		}
	}
}
