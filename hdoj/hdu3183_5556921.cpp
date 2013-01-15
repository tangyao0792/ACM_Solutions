/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>
#include<cmath>

#define min(a,b) (s[a]<=s[b]?a:b)

char s[1010];
int n,m;

int st[1010][10];

void SparseTable()
{
    for(int i=0;i<n;i++)    st[i][0]=i;

    for(int j=1;1<<j <=n; j++)
        for(int i=0; i+(1<<(j-1)) <=n; i++)
            st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
}

int get(int l, int r)
{
    int k=int(log(double(1+r-l))/log(2.0));
    return min(st[l][k],st[r-(1<<k)+1][k]);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%s %d",s,&m)==2)
    {
        n=strlen(s);
        SparseTable();
        int l=0;
        char ans[1010];
        memset(ans,0,sizeof(ans));
        int p=0;
        m=n-m;
        int zero=0;
        while(m--)
        {
            l=get(l,n-m-1);
            ans[p++]=s[l];
            zero+=s[l]-'0';
            l++;
        }
        if(!zero)
        {
            printf("0\n");
        }
        else
        {
            l=0;
            while(ans[l]=='0')l++;
            printf("%s\n",&ans[l]);
        }
    }
    return 0;
}
