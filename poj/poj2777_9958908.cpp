#include<cstdio>
#include<cstring>

const int MAXN=100100;
const int MAXT=50;

int color[MAXN*4];
bool in[MAXT];
bool mix[MAXN*4];

void PushDown(int pos)
{
    if(!mix[pos])
    {
        mix[pos<<1]=mix[pos<<1|1]=false;
        color[pos<<1]=color[pos<<1|1]=color[pos];
        mix[pos]=true;
    }
}

void PushUp(int pos)
{
    if(color[pos<<1] == color[pos<<1|1] && !mix[pos<<1] && !mix[pos<<1|1])
    {
        color[pos]=color[pos<<1];
        mix[pos]=false;
    }
    else
        mix[pos]=true;
}

void update(int a,int b,int v,int l,int r,int pos)
{

    if(a<=l && b>=r)
    {
        mix[pos]=false;
        color[pos]=v;
        return;
    }

    if(l==r)    return;
    int mid=(l+r)>>1;
    PushDown(pos);

    if(a<=mid)
        update(a,b,v,l,mid,pos<<1);
    if(b>mid)
        update(a,b,v,mid+1,r,pos<<1|1);

    PushUp(pos);
}
void query(int a,int b,int l,int r,int pos)
{
    if(!mix[pos])
    {
        in[color[pos]]=true;
        return;
    }

    PushDown(pos);

    if(l==r)    return;

    int mid=(l+r)>>1;


    if(a<=mid)
        query(a,b,l,mid,pos<<1);
    if(b>mid)
        query(a,b,mid+1,r,pos<<1|1);

    PushUp(pos);
}

void build(int l,int r,int pos)
{
    if(l==r)
    {
        color[pos]=1;
        return;
    }
    int mid=(l+r)>>1;

    build(l,mid,pos<<1);
    build(mid+1,r,pos<<1|1);

    PushUp(pos);
}
void swap(int &a,int &b)
{
    int tmp=a;
    a=b;
    b=tmp;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,t,o;
    char op[10];
    scanf("%d %d %d",&n,&t,&o);
    {
        build(1,n,1);
        for(int i=0;i<o;i++)
        {
            scanf("%s",op);
            if(op[0]=='C')
            {
                int a,b,c;
                scanf("%d %d %d",&a,&b,&c);
                if(a>b)
                    swap(a,b);
                update(a,b,c,1,n,1);
            }
            else
            {
                int a,b;
                scanf("%d %d",&a,&b);
                memset(in,0,sizeof(in));
                if(a>b )
                    swap(a,b);
                query(a,b,1,n,1);
                int ans=0;

                for(int i=1;i<=t;i++)
                    if(in[i])
                        ans++;

                printf("%d\n",ans);
            }
        }
    }
    return 0;
}
