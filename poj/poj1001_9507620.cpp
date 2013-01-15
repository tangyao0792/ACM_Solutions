#include<stdio.h>

void main()
{
	char input[6];
	int result[125];
	int temp[125];
	int mul[5];
	int n, length,count;						//length表示输入的乘数小数点后有哦几位，count表示结果小数点后有多少无用的0
	int i, j, k, of;
	while(scanf("%s %d", input, &n) != EOF)
	{
		
		for(i = 0; i < 125; i++)
		{
			result[i] = temp[i] = 0;
		}
		j = i = 0;
		while(i < 6)
		{
			if(input[i] == '.')
			{
				length = 5 - i;
				i++;
				continue;
			}
			result[120+j] = mul[j] = input[i++] - 48;
			j++;
		}

		for(i = 1; i < n; i++)
		{
			for(j = 4; j > -1; j--)
			{
				for(k = 124, of = 0; j+k-4 > -1; k--)
				{
					temp[j+k-4] += result[k] * mul[j] + of;
					of = temp[j+k-4] / 10;
					temp[j+k-4] = temp[j+k-4] % 10;
				}
			}
			for(k = 0; k < 125; k++)
			{
				result[k] = temp[k];
				temp[k] = 0;
			}

		}
		for(i = 124,count = 0; i > -1 && i > 124-n*length; i--)		//计算结果的小数位最后0的数量
		{
			if( result[i] == 0)
			{
				count++;
			}
			else
			{
				break;
			}
		}
		i = 0;
		while(result[i] == 0 && i < 124 - n* length+1)
		{
			i++;
		}

		for(; i < 125-count; i++)
		{
			if(i == 124-n*length+1)
			{
				printf(".");
			}
			printf("%d", result[i]);
		}
		printf("\n");
	}
}
