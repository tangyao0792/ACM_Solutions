/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<iostream>
using namespace std;
int pre[19];
int map[18][18];
__int64 hash[1<<18][18];
int N,M;
int main()
{
    __int64 sum;
    int i,j,k,s,e,len;
    pre[0]=1;
    for(i=1;i<19;i++)
        pre[i]=pre[i-1]<<1;
    while(scanf("%d %d",&N,&M)!=EOF)
    {
        memset(map,0,sizeof(map));
        for(i=0;i<M;i++)
        {
            scanf("%d %d",&s,&e);
            if(s==e)
                continue;
            s--,e--;
            map[s][e]=1;
            map[e][s]=1;
        }
        len=pre[N];
        for(i=0;i<len;i++)
        {
            for(j=0;j<N;j++)
            {
                hash[i][j]=0;
            }
        }
        hash[1][0]=1;
        for(i=1;i<len;i++)
        {
            for(j=0;j<N;j++)
            {
                if((i&pre[j])==0)
                    continue;
                for(k=0;k<N;k++)
                {
                    if((i&pre[k])==0&&map[j][k]==1)
                        hash[i|pre[k]][k]+=hash[i][j];
                }
            }
        }
        sum=0;
        for(i=1;i<N;i++)
            if(map[i][0]==1)
                sum+=hash[pre[N]-1][i];
        printf("%I64d\n",sum);
    }
    return 0;
}
