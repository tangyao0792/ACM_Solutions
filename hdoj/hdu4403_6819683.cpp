/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

using namespace std;

char str[22];
long long  a[22],b[22][22];
long long  l[15][11000],r[15][11100];
int nl[22],nr[22];

int main(int argc, const char *argv[])
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    while(gets(str))
    {
        if(str[0]=='E')
            break;

        int n=strlen(str);
        for(int i=0;i<n;i++)
            a[i]=str[i]-'0';

        memset(nl,0,sizeof(nl));
        memset(nr,0,sizeof(nr));

        for(int i=0;i<n;i++)
        {
            long long tmp=0;
            for(int j=i;j<n;j++)
            {
                tmp=tmp*10+a[j];
                b[i][j]=tmp;
//                printf("%d %d:    %lld\n",i,j,b[i][j]);
            }
        }

        for(int i=0;i<n;i++)
        {
            l[i][nl[i]++]=b[0][i];
        }

        for(int i=n-1;i>=0;i--)
        {
            r[i][nr[i]++]=b[i][n-1];
        }

        for(int i=1;i<n;i++)
        {
            for(int j=i;j>=1;j--)
            {
                for(int k=0;k<nl[j-1];k++)
                {
                    l[i][nl[i]++]=l[j-1][k]+b[j][i];
                }
            }
        }

        for(int i=n-1;i>=0;i--)
        {
            for(int j=i;j<n-1;j++)
            {
                for(int k=0;k<nr[j+1];k++)
                {
                    r[i][nr[i]++]=r[j+1][k]+b[i][j];
                }
            }
        }
        int ans=0;
        for(int i=0;i<n-1;i++)
        {
            for(int j=0;j<nl[i];j++)
            {
                for(int k=0;k<nr[i+1];k++)
                {
                    if(l[i][j]==r[i+1][k])
                        ans++;
                }
            }
        }
        printf("%d\n",ans);

    }
    return 0;
}
