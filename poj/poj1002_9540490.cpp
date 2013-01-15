#include<stdio.h>
#include<stdlib.h>
int cmp(const void* ,const void*);
void main()
{
	int n;
	int x;
	char temp[101];
	int i, j;
	int flag = 0;
	int num[100000];
	int count;
	scanf("%d", &n);
	for( i = 0; i < n; i++)
	{
		scanf("%s", temp);
		x = 0;
		for(j = 0; temp[j]; j++)
		{

			if(temp[j] == 'Q' || temp[j] == '-')
			{
				continue;
			}
			else if((temp[j] >'0'-1) && (temp[j] < '9' +1))
			{
				x = x*10 + temp[j] - 48;			
			}
			else if(temp[j] > 'A'- 1 && temp[j] <'Z')
			{
				switch (temp[j])
				{
				case 'A':
				case 'B':
				case 'C':
					x = x*10 +2;break;
				case 'D':
				case 'E':
				case 'F':
					x = x * 10 +3; break;
				case 'G':
				case 'H':
				case 'I':
					x = x * 10 + 4;break;
				case 'J':
				case 'K':
				case 'L': 
					x = x *10 +5; break;
				case 'M':
				case 'N':
				case 'O':
					x = x * 10 + 6; break;
				case 'P':
				case 'R':
				case 'S':
					x = x*10 +7; break;
				case 'T':
				case 'U':
				case 'V':
					x = x*10 +8;break;
				case 'W':
				case 'X':
				case 'Y':
					x = x * 10 + 9; break;
				default:
					;
				}
			}
		}
		num[i] = x;
	}
	
	qsort(num,n,sizeof(int),cmp);
	
	for(i = 0; i < n; i++)
	{
		count = 1;
		while(num[i] == num[i+1])
		{
			i++;
			count++;
		}
		if(count > 1)
		{
			printf("%03d-%04d %d\n",num[i]/10000, num[i]%10000,count);
			flag = 1;
		}
	}
	if( flag == 0 )
	{
		printf("No duplicates.");
	}

}
int cmp(const void* a,const void *b)
{
	return *(int*)a-*(int*)b;
}
