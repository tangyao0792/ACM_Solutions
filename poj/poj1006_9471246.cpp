#include <stdio.h>

void main()
{
	int a, b, c, d;
	int cycle;
	int day;
	int i = 0;
	scanf("%d %d %d %d", &a, &b, &c, &d);
	while(a != -1)
	{
		i++;
		a = a % 23;
		b = b % 28;
		c = c % 33;
		cycle = 28 * 33 * 6 * a + 23 * 33 * 19 * b + 23 * 28 * 2 * c;
		cycle = cycle % 21252;
		day = (cycle - d) % 21252 + 21252;
		day = day % 21252;
		if(day == 0)
		{
			day = 21252;
		}
		printf("Case %d: the next triple peak occurs in %d days.\n", i, day);
		scanf("%d %d %d %d", &a, &b, &c, &d);
	}
}
