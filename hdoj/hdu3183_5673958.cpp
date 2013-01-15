/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>
#include<cmath>

#define min(a,b) (str[a]<=str[b]?a:b)

const int MAXN=1010;

char str[MAXN];
char ans[MAXN];
int st[20][MAXN];
int n;

void SparseTable()
{
    for(int i=0;i<n;i++)
        st[0][i]=i;

    for(int j=1;1<<j <=n;j++)
        for(int i=0;i+(1<<(j-1)) <=n;i++)
            st[j][i]=min(st[j-1][i],st[j-1][i+(1<<(j-1))]);
}

int get(int x,int y)
{
    int k=int(log(double(y-x+1))/log(2.0));

    return min(st[k][x],st[k][y-(1<<k)+1]);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int m;
    while(scanf("%s %d",str,&m)==2)
    {
        n=strlen(str);
        SparseTable();
        int k=0;

        memset(ans,0,sizeof(ans));
        int p=0;
        for(int i=0;i<n-m;i++)
        {
            k=get(k,m+i);
            ans[p++]=str[k];
            k++;
        }
        int j=0;
        while(ans[j]=='0' && j<p-1)j++;

        for(;j<p;j++)
           printf("%c",ans[j]);
        if(p==0)
            printf("0");
        printf("\n");
    }

    return 0;
}
