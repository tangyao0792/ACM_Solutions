#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

const int MAXN=50;
const int INF=1<<28;
const char *XXL="XXL";
const char *XL="XL";
const char *L="L";
const char *M="M";
const char *S="S";
const char *XS="XS";

int cap[MAXN][MAXN],flow[MAXN][MAXN],a[MAXN],fa[MAXN];//40-45´¢´æÒÂ·þ46½áÊø
int n,m;

int changeToNum(char *s);
int EK();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase;
    scanf("%d",&nCase);
    while(nCase--)
    {
        memset(cap,0,sizeof(cap));
        memset(flow,0,sizeof(flow));
        scanf("%d %d",&n,&m);
        for(int i=40;i<=45;i++)
            cap[i][46]=n/6;
        for(int i=1;i<=m;i++)
        {
            cap[0][i]=1;
            char tmp[5];
            scanf("%s",tmp);
            cap[i][changeToNum(tmp)]=1;
            scanf("%s",tmp);
            cap[i][changeToNum(tmp)]=1;
        }
        if(EK()==m)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}

int EK()
{
    int f=0;
    queue<int> q;
    for(;;)
    {
        memset(a,0,sizeof(a));
        memset(fa,0,sizeof(fa));
        a[0]=INF;
        q.push(0);
        while(!q.empty())
        {
            int x=q.front();
            q.pop();
            for(int v=0;v<=46;v++)
            {
                if(!a[v] && cap[x][v]>flow[x][v])
                {
                    a[v]=min(a[x],cap[x][v]-flow[x][v]);
                    fa[v]=x;
                    q.push(v);
                }
            }
        }

        if(a[46]==0)    break;
        for(int t=46; t!=0;t=fa[t])
        {
            flow[fa[t]][t]+=a[46];
            flow[t][fa[t]]-=a[46];
        }
        f+=a[46];
    }
    return f;
}

int changeToNum(char *s)
{
    if(strcmp(s,XXL)==0)
        return 40;
    if(strcmp(s,XL)==0)
        return 41;
    if(strcmp(s,L)==0)
        return 42;
    if(strcmp(s,M)==0)
        return 43;
    if(strcmp(s,S)==0)
        return 44;
    else
        return 45;
}
