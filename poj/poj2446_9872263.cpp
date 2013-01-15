#include<cstdio>
#include<cstring>

const int MAXM=35*35*4;
const int MAXN=35*35;

bool g[35][35],chk[MAXN];
int u[MAXM],v[MAXM],next[MAXM];
int xM[MAXN],yM[MAXN],first[MAXN];
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
int a,b,k,cnt;

bool SearchPath(int u)
{
    chk[u]=true;
    for(int e=first[u];e!=-1;e=next[e])
    {
        if(!chk[v[e]])
        {
            chk[v[e]]=true;
            if(yM[v[e]]==-1 || SearchPath(yM[v[e]]))
            {
                yM[v[e]]=u;xM[u]=v[e];
                return true;
            }
        }
    }
    return false;
}

int MaxMatch()
{
    int ans=0;
    memset(xM,-1,sizeof(xM));
    memset(yM,-1,sizeof(yM));
    int t=a*b;
    for(int u=1;u<=t;u++)
    {
        if(xM[u]==-1)
        {
            memset(chk,0,sizeof(chk));
            if(SearchPath(u))   ans++;
        }
    }
    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    scanf("%d %d %d",&a,&b,&k);
    {
        memset(g,0,sizeof(g));
        memset(first,-1,sizeof(first));
        for(int i=0;i<k;i++)
        {
            int x,y;
            scanf("%d %d",&y,&x);
            g[x][y]=true;
        }
        cnt=0;
        for(int i=1;i<=a;i++)
            for(int j=1;j<=b;j++)
                if(!g[i][j])
                {
                    for(int x=0;x<4;x++)
                    {
                        int from=i*b+j-b;
                        int nx=i+dx[x];
                        int ny=j+dy[x];
                        if(nx>0&&nx<=a&&ny>0&&ny<=b&&(!g[nx][ny]))
                        {
                            int to=nx*b+ny-b;
                            u[cnt]=from;
                            v[cnt]=to;
                            next[cnt]=first[from];
                            first[from]=cnt++;
                        }
                    }
                }
        if((a*b-k)%2==0 && MaxMatch()==a*b-k)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
