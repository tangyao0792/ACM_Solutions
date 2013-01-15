#include<cstdio>
#include<cstring>

int v[6];
int w[20010];
int dp[20010*6];

bool solve(int sum)
{
    int cnt=1;
    if(sum%2==1)    return false;
    sum/=2;

    for(int i=0;i<6;i++)
    {
        int tmp=0;
        for(int k=1;k<v[i];k*=2)
        {
            w[cnt++]=(i+1)*k;
            tmp+=(i+1)*k;
        }
        if(tmp<v[i]*(i+1))
        {
            w[cnt]=v[i]*(i+1)-tmp;
            cnt++;
        }
    }
    memset(dp,0,sizeof(dp));
    dp[0]=1;

    for(int i=1;i<cnt;i++)
        for(int v=sum;v>=w[i];v--)
            if(dp[v-w[i]])
                dp[v]=1;

    if(dp[sum])   return true;

    return false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif

    int nCase=0;
    while(true)
    {
        int sum=0;
        for(int i=0;i<6;i++)
        {
            scanf("%d",&v[i]);
            sum+=v[i]*(i+1);
        }
        if(!sum)    break;

        nCase++;
        printf("Collection #%d:\n",nCase);
        if(solve(sum))
        {
            printf("Can be divided.\n");
        }
        else
        {
            printf("Can't be divided.\n");
        }
        printf("\n");
    }
    return 0;
}
