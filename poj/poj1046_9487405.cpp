#include<stdio.h>

void main()
{
	int target[16][3];
	int input[3];
	int minDistance = 0;
	int tempDistance = 0;
	int index;
	int i = 0;
	for(; i < 16; i++)
	{
		scanf("%d %d %d",target[i], target[i]+1 , target[i] +2);
	}

	scanf("%d %d %d", input, input +1, input +2);
	while(input[0] != -1)
	{
		for(i = 0,index = 0; i < 16; i++)
		{
			tempDistance = (target[i][0] - input[0]) * (target[i][0] - input[0])  + (target[i][1]- input[1]) * (target[i][1]- input[1])
				+ (target[i][2]- input[2]) *(target[i][2]- input[2]) ;
			if( i == 0)
			{
				minDistance = tempDistance;
				index = 0;
			}
			else
			{
				if(tempDistance < minDistance)
				{
					minDistance = tempDistance;
					index = i;
				}
			}
		}
		printf("(%d,%d,%d) maps to (%d,%d,%d)\n", input[0], input[1], input[2], target[index][0], target[index][1], target[index][2]);

		scanf("%d %d %d", input, input +1, input +2);
	
	
	}

}
