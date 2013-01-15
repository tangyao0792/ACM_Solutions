/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<algorithm>

using namespace std;

const int MAXN = 110;
const int MAXM = 110*110/2;

int n, m;
int w[MAXM],u[MAXM],v[MAXM],r[MAXM];
int p[MAXN];
bool flag;
int ans;

bool comp(int a, int b);
int find(int x);
void kruskal();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while( scanf("%d %d", &m, &n) && m)
    {
        for(int i = 0; i <= n; i++) p[i] = i;
        for(int i = 0; i < m; i++)
        {
            scanf("%d %d %d",&u[i],&v[i],&w[i]);
        }
        kruskal();
        if(flag)    printf("%d\n",ans);
        else    printf("?\n");
    }
    return 0;
}

void kruskal()
{
    flag = false;
    ans = 0;
    for(int i = 0; i < m; i++) r[i] = i;
    sort(r, r+m, comp);
    int cnt = 0;
    for(int i = 0; i < m; i++)
    {
        int e = r[i];
        int x = find(u[e]);
        int y = find(v[e]);
        if(x != y)
        {
            ans += w[e];
            p[x] = y;
            cnt++;
        }
    }
    if(cnt != n-1)  return ;
    flag = true;
}

bool comp(int a, int b)
{
    return w[a]<w[b];
}
int find(int x)
{
    return p[x]==x?x:(p[x]=find(p[x]));
}
