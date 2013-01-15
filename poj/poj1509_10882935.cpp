#include<cstdio>
#include<cstring>

#define min(a,b) (a<b?a:b)

const int MAXN=10010;

char str[MAXN];

int MinimumRepresentation(char *s,int l)//串s[0~l-1]的最小表示位置
{

	int i = 0, j = 1, k = 0,t;
	while (i < l && j < l && k < l)//找不到比它还小的 或者 完全匹配
	{

		t = s[(i+k)%l] - s[(j+k)%l];
		//if (s[(i+k) >= l ? i+k-l : i+k] == s[(j+k) >= l ? j+k-l : j+k])
		if (t == 0)
			k++;//相等的话,检测长度加1
		else 
		{

			if (t > 0)//大于的话,s[i]为首的肯定不是最小表示,最大表示就改<
				i += k + 1;
			else
				j += k + 1;
			if (i == j)
				j++;
			k = 0;
		} 
	} 
	return min(i,j);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%s",str);
		printf("%d\n",MinimumRepresentation(str,strlen(str))+1);
	}
	return 0;
}
