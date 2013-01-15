#include<stdio.h>
#include<string.h>
void main()
{
	char haab[19][10] =
	{"pop", "no", "zip", "zotz", "tzec", "xul", "yoxkin", "mol", "chen"
	, "yax", "zac", "ceh", "mac", "kankin", "muan", "pax", "koyab", "cumhu","uayet"};
	
	char tzolkin[20][10] =
	{"imix", "ik", "akbal", "kan", "chicchan", "cimi", "manik", "lamat", "muluk",
	"ok", "chuen", "eb", "ben", "ix", "mem", "cib", "caban", "eznab", "canac", "ahau"		
	};

	int n, i, j;
	char month[10];
	int year, index,total;
	int day;
	
	scanf("%d", &n);
	printf("%d\n",n);
	for(i = 0; i < n; i++)
	{
		scanf("%d. %s %d",&day,month,&year);
		for(j = 0; j < 19; j++)
		{
			if( strcmp(month,haab[j]) == 0)
			{
				index = j;
				break;
			}
		}
		total = day + year * 365 + index * 20;
		year = total / 260;
		day = total % 260;
		index = day %20 ;
		day = day %13 +1;
		printf("%d %s %d\n",day,tzolkin[index],year);
	}

}
