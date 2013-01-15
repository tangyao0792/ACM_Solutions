#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

const int MAXN=2*10010;

struct Line
{
    int li,num;
}line[MAXN];

struct Tree
{
    int l,r,c;
}T[MAXN*4];

int set[MAXN][2],vis[MAXN];
int n,ans;

bool comp(Line x,Line y)
{
    return x.li<y.li;
}


void build(int s,int t,int pos)
{
    T[pos].l=s;
    T[pos].r=t;
    T[pos].c=0;

    if(s==t)    return;

    int mid=(s+t)>>1;

    build(s,mid,2*pos);
    build(mid+1,t,2*pos+1);
}

void ins(int s,int t,int id,int pos)
{
    if(s==T[pos].l && t==T[pos].r)
    {
        T[pos].c=id;
        return;
    }
    if(T[pos].c != 0)
    {
        T[pos*2].c=T[pos].c;
        T[pos*2+1].c=T[pos].c;
        T[pos].c=0;
    }
    int l=T[pos].l;
    int r=T[pos].r;

    int mid=(l+r)>>1;

    if(mid>=t)
    {
        ins(s,t,id,2*pos);
    }
    else if(mid<s)
    {
        ins(s,t,id,2*pos+1);
    }
    else
    {
        ins(s,mid,id,pos*2);
        ins(mid+1,t,id,pos*2+1);
    }
}

void find(int pos)
{
    if(T[pos].c!=0 )
    {
        if(!vis[T[pos].c])
        {
            ans++;
            vis[T[pos].c]=1;
        }
        return;
    }
    int l=T[pos].l,r=T[pos].r;
    if(l==r)    return;

    find(pos*2);
    find(pos*2+1);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    int nCase;
    while(scanf("%d",&nCase)==1)
    while(nCase--)
    {
        scanf("%d",&n);
        for(int i=0;i<n;i++)
        {
            int x,y;
            scanf("%d %d",&x,&y);
            set[i][0]=x;set[i][1]=y;
            line[i*2].li=x;
            line[i*2].num=-i-1;
            line[i*2+1].li=y;
            line[i*2+1].num=i+1;
        }
        sort(line,line+2*n,comp);
        int tmp=line[0].li;int tp=1;

        for(int i=0;i<2*n;i++)
        {
            if(tmp!=line[i].li)
            {
                tp++;
                tmp=line[i].li;
            }
            if(line[i].num<0)
                set[-line[i].num-1][0]=tp;
            else
                set[line[i].num-1][1]=tp;
        }

        build(1,tp,1);

        for(int i=0;i<n;i++)
            ins(set[i][0],set[i][1],i+1,1);

        memset(vis,0,sizeof(vis));
        ans=0;
        find(1);
        printf("%d\n",ans);
    }
    return 0;
}
