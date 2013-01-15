#include<cstdio>

#define max(a,b) (a>b?a:b)

using namespace std;

const int MAXN=710;

int a[MAXN],b[MAXN];
int x,y;
int u,v;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    int n,cnt;
    while(scanf("%d",&n)==1 && n)
    {
        for(int i=0;i<n;i++)
        {
            scanf("%d %d",&a[i],&b[i]);
        }
        int nMax=0;
        for(int i=0;i<n;i++)
        {
            for(int j=i+1;j<n;j++)
            {
                cnt=0;
                x=a[i]-a[j];
                y=b[i]-b[j];
                for(int k=j+1;k<n;k++)
                {
                  //  if(k==i || k==j)    continue;
                    u=a[i]-a[k];
                    v=b[i]-b[k];
                    if(x*v==y*u)
                        cnt++;
                }
                nMax=max(nMax,cnt);
            }
        }
        printf("%d\n",nMax+2);
    }
    return 0;
}
