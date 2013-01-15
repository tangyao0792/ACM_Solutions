#include <stdio.h>
#include <math.h>
const double PI = 3.1415926;
void main()
{
	int n;
	int count;
	int i;
	double dist;
	double radius;
	double area = 0;
	double x,y;
	scanf("%d",&n);
	for( i = 0; i < n; i++)
	{
		scanf("%lf %lf",&x,&y);
		dist = sqrt(x * x + y * y);
		area = 0;
		radius = 0;
		count = 0;
		while(dist > radius)
		{
			area += 50;
			radius = sqrt (area * 2 / PI );
			count++;
		}
		printf("Property %d: This property will begin eroding in year %d.\n", i +1 ,count );
	}
	
	printf("END OF OUTPUT.\n");

}
