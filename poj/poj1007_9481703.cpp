#include<stdio.h>
#include<string.h>

int inversion(char[]);

void main()
{
	char dna[100][51];
	char temp[51];
	int n, m;
	int i, j, k;
	scanf("%d %d", &n, &m);
	for(i = 0; i< m; i++)
	{
		scanf("%s",temp);
		if(i == 0)
		{
			strcpy(dna[i],temp);
		}
		else
		{
			for(j =i-1 ; j > -1; j--)
			{
				if( inversion(temp) > inversion(dna[j]))
				{
					break;
				}
			}
			
			for(k = i; k > j ; k--)
			{
				strcpy(dna[k], dna[k-1]);
			}
			strcpy(dna[j+1],temp);
		}		
	}	

	for(i = 0; i < m; i++)
	{
		printf("%s\n", dna[i]);
	}
	
}

int inversion(char str[])
{
	int length = strlen( str);
	int count = 0;
	int i, j;
	for(i =0; i < length; i++)
	{
		for(j =i+1; j < length; j++)
		{
			if(str[j] < str[i])
			{
				count++;
			}
		}
	}

	return count;
}
