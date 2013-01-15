#include<stdio.h>
#include<string.h>
void main()
{
	char input[100], in[27];
	int n;
	int i, length;
	int num;
	scanf("%d", &n);
	while( n > 0)
	{
		scanf("%s", input);
		length = strlen(input);
		for(i = 0; i < 26; i++)
		{
			in[i] = 0;
		}
		for(i = 0, num = 0; i < length; i++)
		{
			if( in[input[i] - 'A'] == 1)
			{
				in[input[i] - 'A'] = 0;
				n++;
			}
			else
			{
				in[input[i] - 'A'] = 1;			//即使没有床位也要记录，因为离开的时候要执行if后的语句块
				n--;							//n允许负数，因为离开的时候n要自增	
				if(n < 0)
				{
					num++;
				}
			}
		}

		if( num == 0)
		{
			printf("All customers tanned successfully.\n");
		}
		else
		{
			printf("%d customer(s) walked away.\n", num);
		}
		scanf("%d", &n);
	}
}
