/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

#define abs(a) ((a)>0?(a):-(a))

using namespace std;

const int INF=1<<29;

struct node
{
    int p,w;
    bool operator < (const node &t)const
    {
        return p < t.p;
    }
}ball[55][1111];
int dp[55][1111];
int n,m;

inline void readint(int &ret)
{
    char c;
    do {    c = getchar();
    } while(c < '0' || c > '9');
    ret = c - '0';
    while((c=getchar()) >= '0' && c <= '9')
        ret = ret * 10 + ( c - '0' );
}

inline int cost(int pa,int pb,int c)
{
    return abs(pa-pb)+c;
}

int q[1111],front,rear;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("data.in","r",stdin);
    freopen("out.txt","w",stdout);
#endif
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int pos;
        scanf("%d %d %d",&m,&n,&pos);
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++)
                readint(ball[i][j].p);
            //    scanf("%d",&ball[i][j].p);

        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++)
                readint(ball[i][j].w);
                //scanf("%d",&ball[i][j].w);

        for(int i=0;i<m;i++)
            sort(ball[i],ball[i]+n);

        for(int i=0;i<n;i++)
            dp[0][i]=cost(pos,ball[0][i].p,ball[0][i].w);
        for(int i=1;i<m;i++)
        {
            q[0]=0;
            rear=0;
            int k=0,j=0;
            for(;j<n;j++)
            {
                dp[i][j]=INF;
                while(k<n && ball[i-1][k].p<=ball[i][j].p)
                {
                    while(q[rear-1]>(dp[i-1][k]-ball[i-1][k].p)  && rear)
                        rear--;
                    q[rear++]=dp[i-1][k]-ball[i-1][k].p;
                    k++;
                }
                if(rear>0)
                    dp[i][j]=min(dp[i][j],q[0]+ball[i][j].p+ball[i][j].w);
            }
            q[0]=0;
            rear=0;
            k=n-1,j=n-1;
            for(;j>=0;j--)
            {
                while(k>=0 && ball[i-1][k].p>=ball[i][j].p)
                {
                    while(q[rear-1]>(dp[i-1][k]+ball[i-1][k].p)  && rear)
                        rear--;
                    q[rear++]=dp[i-1][k]+ball[i-1][k].p;
                    k--;
                }
                if(rear>0)
                    dp[i][j]=min(dp[i][j],q[0]-ball[i][j].p+ball[i][j].w);
            }
        }
        int ans=INF;
        for(int i=0;i<n;i++)
            ans=min(ans,dp[m-1][i]);
        printf("%d\n",ans);
    }

    return 0;
}
