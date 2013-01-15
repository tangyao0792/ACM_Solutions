/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>
#include<cmath>

const int MAXN=1<<18;

int n,M;
int T[MAXN];

int query(int s,int t)
{
    int    ans=0;
    for(s=s+M-1,t=t+M+1;s^t^1;s>>=1,t>>=1)
    {
        if(~s&1)    ans+=T[s^1];
        if(t&1)    ans+=T[t^1];
    }
    return ans;
}

void update(int n,int v)
{
    n+=M;
    T[n]+=v;
    while(n>1)
    {
        n=n>>1;
        T[n]=T[2*n]+T[2*n+1];
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif

    int t;
    scanf("%d",&t);
    int nCase=1;
    while(t--)
    {
        scanf("%d",&n);
        memset(T,0,sizeof(T));

        M=log(n)/log(2)+1;
        M=pow(2,M);

        for(int i=0;i<n;i++)
        {
            int tmp;
            scanf("%d",&tmp);
            update(i+1,tmp);
        }
        char str[20];
        printf("Case %d:\n",nCase++);

        while(~scanf("%s",str))
        {
            if(strcmp(str,"End")==0)
            {
                break;
            }
            if(strcmp(str,"Query")==0)
            {
                int a,b;
                scanf("%d %d",&a,&b);
                printf("%d\n",query(a,b));
            }
            if(str[0]=='S')
            {
                int a,b;
                scanf("%d %d",&a,&b);
                update(a,-b);
            }
            if(str[0]=='A')
            {
                int a,b;
                scanf("%d %d",&a,&b);
                update(a,b);
            }
        }
    }
    return 0;
}
