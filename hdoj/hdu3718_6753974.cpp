/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

#define MAXN 60
#define inf 1000000000
int min_cost_max_flow(int n,int mat[][MAXN],int cost[][MAXN],int source,int sink,int
        flow[][MAXN],int& netcost){


    int pre[MAXN],min[MAXN],d[MAXN],i,j,t,tag;
    if (source==sink) return inf;
    for (i=0;i<n;i++)
        for (j=0;j<n;flow[i][j++]=0);
    for (netcost=0;;){


        for (i=0;i<n;i++)
            pre[i]=0,min[i]=inf;
        for (pre[source]=source+1,min[source]=0,d[source]=inf,tag=1;tag;)
            for (tag=t=0;t<n;t++)
                if (d[t])
                    for (i=0;i<n;i++)
                        if (j=mat[t][i]-flow[t][i]&&min[t]+cost[t][i]<min[i])
                            tag=1,min[i]=min[t]+cost[t][i],pre[i]=t+1,d[i]=d[t]<j?d[t]:j;
                        else if (j=flow[i][t]&&min[t]<inf&&min[t]-cost[i][t]<min[i])
                            tag=1,min[i]=min[t]-cost[i][t],pre[i]=-t-1,d[i]=d[t]<j?d[t]:j;
        if (!pre[sink]) break;
        for (netcost+=min[sink]*d[i=sink];i!=source;)
            if (pre[i]>0)
                flow[pre[i]-1][i]+=d[sink],i=pre[i]-1;
            else
                flow[i][-pre[i]-1]-=d[sink],i=-pre[i]-1;
    }
    for (j=i=0;i<n; j+=flow[source][i++]);
    return j;
}

int hash[300][11000];    //hash['A']
int num[333];
int n,k,m;
int ans[11000];

int mat[60][60],cost[60][60];
int flow[60][60];

int main()
{

#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    int t;
    scanf("%d",&t);
    while(t--)
    {

        scanf("%d %d %d\n",&n,&k,&m);
        memset(num,0,sizeof(num));
        memset(mat,0,sizeof(mat));

        for(int i=0;i<n;i++)
        {
            char c[3];
            scanf("%s",c);
            ans[i]=c[0]-'A';
        }
        for(int i=0;i<60;i++)
            for(int j=0;j<60;j++)
                cost[i][j]=inf;

        for(int i=0;i<m;i++)
        {
            memset(num,0,sizeof(num));
            memset(mat,0,sizeof(mat));

            for(int i=0;i<60;i++)
                for(int j=0;j<60;j++)
                cost[i][j]=inf;

            for(int j=0;j<n;j++)
            {
                char c[3];
                scanf("%s",c);
//                puts(c);
                int x=c[0]-'A';
                hash[ans[j]][num[ans[j]]++]=x;
            }


            for(int j=0;j<26;j++)        //change j to k
            {
                for(int k=0;k<26;k++)
                {
                    int tmp=0;
                    for(int l=0;l<num[j];l++)
                    {
                        if(hash[j][l]!=k)
                            tmp++;
                    }
                    if(num[j])
                    {
                        mat[j][k+26]=1;
                        cost[j][k+26]=tmp;
                    }
                }
            }
            for(int j=0;j<26;j++)
            {
                mat[55][j]=1;
                cost[55][j]=0;
                mat[j+26][56]=1;
                cost[j+26][56]=0;
            }
            int t;
            min_cost_max_flow(60,mat,cost,55,56,flow,t);
            printf("%.4f\n",double(n-t)/double(n));
        }

    }
    return 0;
}
