#include<cstdio>
#include<cstring>

const int MAXN=250010;
const int MAXM=15;
const int tk=26,tb='a';

int top;
int tree[MAXN*MAXM][tk+1];
int d[MAXN*2],p[MAXN*2];

void init()
{
    top=1;
    memset(tree[0],0,sizeof(tree[0]));
}

int sear(char *s)
{
    for(int rt=0;(rt=tree[rt][*s-tb]);)
        if(*(++s)==0)
            return tree[rt][tk];
    return -1;
}

void insert(char*s, int rank)
{
    int rt,nxt;
    for(rt=0;*s;rt=nxt,s++)
    {
        nxt=tree[rt][*s-tb];
        if(nxt==0)
        {
            tree[rt][*s-tb]=nxt=top;
            memset(tree[top],0,sizeof(tree[top]));
            top++;
        }
    }
    tree[rt][tk]=rank;
}
int find(int x){return p[x]==-1?x:(p[x]=find(p[x]));}
void unit(int x,int y)
{
    int px=find(x),py=find(y);
    if(px!=py)
        p[px]=py;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    char a[MAXM],b[MAXM];
    int cnt=0;
    init();
    memset(p,-1,sizeof(p));
    memset(d,0,sizeof(d));
    while(scanf("%s %s",a,b)==2)
    {
        int pa=sear(a),pb=sear(b);
        if(pa==-1)
        {
            insert(a,cnt);
            pa=cnt++;
        }
        if(pb==-1)
        {
            insert(b,cnt);
            pb=cnt++;
        }
        unit(pa,pb);
        d[pa]++;d[pb]++;
    }
    bool flag=true;
    int p0=find(0);
    for(int i=1;i<cnt && flag;i++)
    {
        if(p0!=find(i)) flag=false;
    }
    int cnte=0;
    for(int i=0;i<cnt && flag;i++)
    {
        if(d[i]%2==1)   cnte++;
    }
    if(flag && (cnte==0 || cnte==2))
        printf("Possible\n");
    else
        printf("Impossible\n");
    return 0;
}
