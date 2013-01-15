#include<cstdio>
#include<cstring>

const int MAXN=200010;

struct Tree
{
    int l,r,len;
}T[MAXN*5];

int n,arr[MAXN],p[MAXN],v[MAXN];

void build(int s,int t,int pos)
{
    T[pos].l=s;
    T[pos].r=t;
    T[pos].len=t-s+1;

    if(s==t)    return;

    int mid=(s+t)>>1;

    build(s,mid,pos*2);
    build(mid+1,t,pos*2+1);
}

int find(int p,int pos)
{
    T[pos].len--;
    if(T[pos].l==T[pos].r)
        return T[pos].l;
    if(T[pos*2].len<p)
    {
        return find(p-T[pos*2].len,pos*2+1);
    }

    return    find(p,pos*2);
}
inline void readint(int &ret)
{
	char c;
	do {
	    	c = getchar();
	} while(c < '0' || c > '9');

	ret = c - '0';
	while((c=getchar()) >= '0' && c <= '9')
		ret = ret * 10 + ( c - '0' );
}
char s[100];int sp=0;
inline void outputint(int &ret)
{
    sp=0;
    while(ret)
    {
        s[sp++]=ret%10+'0';
        ret/=10;
    }
    for(int i=sp-1;i>=0;i--)
        putchar(s[i]);
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d",&n)==1)
    {
        build(1,n,1);

        for(int i=0;i<n;i++)
        {
            readint(p[i]);readint(v[i]);
//            scanf("%d %d",&p[i],&v[i]);
        }
        for(int i=n-1;i>=0;i--)
        {
            arr[find(p[i]+1,1)]=v[i];
        }
        printf("%d",arr[1]);
        for(int i=2;i<=n;i++)
            printf(" %d",arr[i]);

        printf("\n");

//        outputint(arr[1]);
//        for(int i=2;i<=n;i++)
//        {
//            putchar(' ');
//            outputint(arr[i]);
//        }
//        puts("");
    }
    return 0;
}
