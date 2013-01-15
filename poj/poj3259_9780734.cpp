#include<cstdio>
#include<iostream>
#include<cstring>

using namespace std;

int w[5500], u[5500],v[5500], d[600];
const int INF = 1<<28;
int N, M, W, cnt;
bool BF(int s);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("wormhole.8.in", "r", stdin);
    freopen("out.txt","w",stdout);
#endif
    int nCase;
    scanf("%d",&nCase);
    while( nCase--)
    {
        scanf("%d %d %d",&N,&M,&W);
        cnt=0;
        for(int i=0;i<M;i++)
        {
            scanf("%d %d %d",&u[cnt],&v[cnt],&w[cnt]);
            w[cnt+1]=w[cnt];
            u[cnt+1]=v[cnt];
            v[cnt+1]=u[cnt];
            cnt+=2;
        }
        for(int i=0;i<W;i++)
        {
            scanf("%d %d %d",&u[cnt],&v[cnt],&w[cnt]);
            w[cnt]=-w[cnt];
            cnt++;
        }
        int k;
        for(k=1;k<=N;k++)
        {
            if(BF(k))
            {
               printf("YES\n");
               break;
            }
        }
        if (k>N)    printf("NO\n");

//
//        if(BF(1))   printf("YES\n");
//        else    printf("NO\n");
    }
    return 0;
}

bool BF(int s)
{
    for(int i=1;i<=N;i++)   d[i]=INF;
    d[s]=0;
    bool flag;
    int k;
    for(k=0;k<N;k++)
    {
        flag = true;
        for(int i=0;i<cnt;i++)
        {
            int x=u[i];
            int y=v[i];
            if(d[x]<INF && d[y]>d[x]+w[i])
            {
                d[y]=d[x]+w[i];
                flag = false;
            }
        }
        if(flag)    break;
    }
    if(k == N)  return true;
    else return false;
}
