/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

const int MAXN=1010;
const int INF=1<<28;

char map[MAXN][MAXN];
char nmap[MAXN][MAXN];

int n,m;
int nLeft[MAXN],nRight[MAXN],a[MAXN];

int max(int a,int b){return a>b?a:b;}

int solve(int r,char c)
{
    if(r==n)
    {
        for(int i=1;i<=m;i++)
        {
            int j=r;
            for(;j>0;j--)
                if(nmap[j][i]!=c)
                    break;

            a[i]=r-j;
        }
    }
    else
    {
        for(int i=1;i<=m;i++)
        {
            a[i]--;
            if(a[i]<0)
            {
                int j=r;
                for(;j>0;j--)
                    if(nmap[j][i]!=c)
                        break;

                a[i]=r-j;
            }
        }
    }

    a[0]=-INF;a[m+1]=-INF;

    for(int i=1;i<=m;i++)
    {
        if(a[i]>a[i-1])
            nLeft[i]=i;
        else
        {
            int t=nLeft[i-1];
            while(a[i]<=a[t-1])
            {
                t=nLeft[t-1];
            }
            nLeft[i]=t;
        }
    }

    for(int i=m;i>=1;i--)
    {
        if(a[i]>a[i+1])
            nRight[i]=i;
        else
        {
            int t=nRight[i+1];
            while(a[i]<=a[t+1])
            {
                t=nRight[t+1];
            }
            nRight[i]=t;
        }
    }

    int s=0;
    int tmp;
    for(int i=1;i<=m;i++)
    {
        tmp=a[i]*(nRight[i]-nLeft[i]+1);
        s=max(s,tmp);
    }
    return s;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif

    while(scanf("%d%d",&n,&m)!=EOF)
    {
        for(int i=1;i<=n;i++)
        {
            scanf("%s",map[i]+1);
        }
        int ans=0;
        memset(a,0,sizeof(a));
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                if(map[i][j]=='w'||
                   map[i][j]=='y'||
                   map[i][j]=='z')
                    nmap[i][j]='a';
                else
                    nmap[i][j]=map[i][j];

        for(int i=n;i>=1;i--)
        {
            int  tmp=solve(i,'a');
            ans=max(tmp,ans);
        }
        memset(a,0,sizeof(a));
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                if(map[i][j]=='w'||
                   map[i][j]=='x'||
                   map[i][j]=='z')
                    nmap[i][j]='b';
                else
                    nmap[i][j]=map[i][j];

        for(int i=n;i>=1;i--)
        {
            int  tmp=solve(i,'b');
            ans=max(tmp,ans);
        }
        memset(a,0,sizeof(a));
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                if(map[i][j]=='x'||
                   map[i][j]=='y'||
                   map[i][j]=='z')
                    nmap[i][j]='c';
                else
                    nmap[i][j]=map[i][j];

        for(int i=n;i>=1;i--)
        {
            int  tmp=solve(i,'c');
            ans=max(tmp,ans);
        }
        printf("%d\n",ans);
    }

    return 0;
}
