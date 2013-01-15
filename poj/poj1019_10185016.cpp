#include<cstdio>
#include<cstring>

typedef long long ll;

const int MAXN=2147483647;

ll a[40001];        //a[i]表示1234...i的长度
ll b[6]={0,45,9045,1395495,189414495ll,23939649495ll};
int c[6]={0,10,100,1000,10000,100000};
int d[10];
int m(long long n)
{
    int i =1;
    while(n/10){i++;n=n/10;}
    return i;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r",stdin);
   // freopen("out2.txt","w",stdout);
#endif

    for(int i =1;i<=40000;i++)
    {
      switch(m(i))
      {
          case 1:a[i] = i;break;
          case 2:a[i] = 2*i - 9;break;
          case 3:a[i] = 3*i-108;break;
          case 4:a[i] = 4*i-1107;break;
          case 5:a[i] = 5*i-11106;break;
        }
    }

    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        scanf("%d",&n);
        int i,j,k;
        for(i=0;i<5;i++)
        {
            if(n>=b[i] && n<b[i+1])
            {
                n-=b[i];
                break;
            }
        }
        if(n==0)
        {
            printf("9\n");
            continue;
        }
        for(j=c[i];a[j]<n;j++)
            n-=a[j];

        int s=0;
        for(k=1;;k++)
        {
            int tmp=m(k);
            if(s+tmp>=n)
            {
                int ss=n-s;
                char str[10];
                sprintf(str,"%d",k);
                printf("%c\n",str[ss-1]);
                break;
            }
            s+=tmp;
        }

    }



    return 0;
}
