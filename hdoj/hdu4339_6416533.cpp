/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

#define lch(pos) (pos<<1)
#define rch(pos) (pos<<1|1)

#define min(a,b) (a<b?a:b)

const int MAXN=1000100;

int t[MAXN*4];

char s[2][MAXN];
int n;

void pushup(int pos,int l,int r)
{
    int mid=(l+r)/2;
    if(t[(pos<<1)]==mid-l+1)
        t[pos]=t[pos<<1]+t[pos<<1|1];
    else
        t[pos]=t[pos<<1];
}

void update(int l,int r,int p,int pos)
{
    if(l==r)
    {
        t[pos]^=1;
        return ;
    }
    int mid=(l+r)/2;

    if(p<=mid)
        update(l,mid,p,pos<<1);
    else
        update(mid+1,r,p,pos<<1|1);

    pushup(pos,l,r);
}


int query(int a,int b,int l,int r,int pos)
{
    if(l>b || a>r)
    {
        return 0;
    }
    if(a<=l && r<=b)
    {
        return t[pos];
    }

   int mid=(l+r)>>1;

   int ans=0;

   if(b<=mid)
   {
       ans=query(a,b,l,mid,pos<<1);
   }
   else if(a>mid)
   {
       ans=query(a,b,mid+1,r,pos<<1|1);
   }
   else
   {
       ans=query(a,b,l,mid,pos<<1);
       if(ans==mid-a+1)
        ans+=query(a,b,mid+1,r,pos<<1|1);
   }

   return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r",stdin);
#endif
    int T;
    scanf("%d",&T);
    int nCase=0;
    while(T--)
    {
        scanf("%s",s[0]);
        scanf("%s",s[1]);


        int len1=strlen(s[0]),len2=strlen(s[1]);
        n=min(len1,len2);
        memset(t,0,sizeof(t));

        for(int i=0;i<n;i++)
        {
            if(s[0][i]==s[1][i])
            {
                update(1,n,i+1,1);
            }
        }

        printf("Case %d:\n",++nCase);

        int q;
        scanf("%d",&q);
        while(q--)
        {
            int c;
            scanf("%d",&c);
            if(c==2)
            {
                int p;
                scanf("%d",&p);
                printf("%d\n",query(p+1,n,1,n,1));
            }
            else
            {
                int no,p;char ch;
                scanf("%d %d %c",&no,&p,&ch);
                if(p>=n) continue;
                no--;
                if((s[no][p]==s[no^1][p] && ch==s[no][p])||
                   (s[no][p]!=s[no^1][p] && ch!=s[no^1][p]))
                {
                    s[no][p]=ch;
                    continue;
                }
                s[no][p]=ch;

                update(1,n,p+1,1);
            }
        }

    }
    return 0;
}
