#include<cstdio>
#include<cstring>

const int MAXN=1000010;

struct node
{
    int p,v;
}q[MAXN];     //qa单调递增队列，qb递减

int a[MAXN];
int f,b;            //指针
int n,m;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r",stdin);
#endif

    scanf("%d %d",&n,&m);



    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);

    f=0;b=-1;
    for(int i=0;i<n;i++)
    {
        while(q[b].v>a[i] && b>f-1)b--;
        b++;
        q[b].v=a[i];q[b].p=i;
        if(i>=m-1)
        {
            while(q[f].p<i-m+1)f++;
            if(i!=m-1)  printf(" ");
            printf("%d",q[f].v);
        }
    }

    printf("\n");

    f=0;b=-1;
    for(int i=0;i<n;i++)
    {
        while(q[b].v<a[i] && b>f-1)b--;
        b++;
        q[b].v=a[i];q[b].p=i;
        if(i>=m-1)
        {
            while(q[f].p<i-m+1)f++;
            if(i!=m-1)  printf(" ");
            printf("%d",q[f].v);
        }
    }

    return 0;
}
