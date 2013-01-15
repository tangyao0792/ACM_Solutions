#include<cstdio>
#include<cstring>

const int MAXN=70000*2;
const int n=65536;

int cover[MAXN*4];  // 覆盖标记,1表示全1,0表示全0，-1表示混合
int x[MAXN*4];      //x==1表示有异或
bool hash[MAXN];

void output()
{
    int cnt=0;

    for(int i=0;i<n*2;i++)
    {
        if(hash[i] && cnt%2==0)
        {
            if(cnt) printf(" ");
            printf(i%2==0?"[%d,":"(%d,",i/2);
            cnt++;
        }
        if(!hash[i] && cnt%2==1)
        {
            printf(i%2==1?"%d]":"%d)",i/2);
            cnt++;
        }
    }
    if(!cnt)
        printf("empty set");
    printf("\n");
}

void PushDown(int pos)
{
    if(cover[pos]!=-1)
    {
        cover[pos<<1]=cover[pos];
        cover[pos<<1|1]=cover[pos];
        x[pos<<1]=0;
        x[pos<<1|1]=0;
        cover[pos]=-1;
    }
    if(x[pos])
    {
        x[pos]=0;
        x[pos<<1]^=1;
        x[pos<<1|1]^=1;
    }
}

void update(int a,int b,int l,int r,int v,int pos)
{
    if(a>r || b<l)
        return;
    if(a<=l && b>=r)
    {
        if(v!=-1)
        {
            cover[pos]=v;
            x[pos]=0;
        }
        else
        {
            if(cover[pos]!=-1)
                cover[pos]^=1;
            else
                x[pos]^=1;
        }
        return;
    }

    int mid=(l+r)>>1;

    PushDown(pos);

    if(a<=mid)
        update(a,b,l,mid,v,pos<<1);
    if(b>mid)
        update(a,b,mid+1,r,v,pos<<1|1);
}

void query(int l,int r,int pos)
{
    if(cover[pos]!=-1)
    {
        if(x[pos] ^ cover[pos])
            for(int i=l;i<=r;i++)
                hash[i]=true;
        return;
    }

    PushDown(pos);

    if(l==r)    return;
    int mid=(l+r)>>1;

    query(l,mid,pos<<1);
    query(mid+1,r,pos<<1|1);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif

    char op[100],s[100];

    memset(hash,0,sizeof(hash));
    memset(x,0,sizeof(x));
    memset(cover,0,sizeof(cover));

    while(~scanf("%s%s",op,s))
    {
        char a,b;int x,y;
        sscanf(s,"%c%d,%d%c",&a,&x,&y,&b);
        int l=(a=='['?x*2:x*2+1);
        int r=(b==']'?y*2:y*2-1);

        if(op[0]=='U')
        {
            update(l,r,0,MAXN,1,1);
        }
        else if(op[0]=='I')
        {
            update(0,l-1,0,MAXN,0,1);
            update(r+1,MAXN,0,MAXN,0,1);
        }
        else if(op[0]=='D')
        {
            update(l,r,0,MAXN,0,1);
        }
        else if(op[0]=='C')
        {
            update(0,l-1,0,MAXN,0,1);
            update(r+1,MAXN,0,MAXN,0,1);
            update(l,r,0,MAXN,-1,1);
        }
        else
        {
            update(l,r,0,MAXN,-1,1);
        }
    }
    query(0,MAXN,1);
    output();

    return 0;
}
