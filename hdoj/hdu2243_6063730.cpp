/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

const int MAXN=35;

typedef unsigned long long ULL;

struct Node
{
    int next[26];
    int fail,cnt;
    void init()
    {
        cnt=fail=0;
        memset(next,0,sizeof(next));
    }
}node[MAXN];



class Matrix
{
public :

    ULL mat[35][35];
    int cnt;

    void init(int n)
    {
        cnt=n;
        memset(mat,0,sizeof(mat));
    }

    Matrix operator *  (const Matrix &tmp) const
    {
        Matrix ans;

        ans.cnt=tmp.cnt;
        for(int i=0;i<cnt;i++)
            for(int j=0;j<cnt;j++)
            {
                ans.mat[i][j]=0;
                for(int k=0;k<cnt;k++)
                    ans.mat[i][j]+=mat[i][k]*tmp.mat[k][j];
            }
        return ans;
    }

    Matrix operator +  (const Matrix &tmp) const
    {
        Matrix ans;
        ans.cnt=tmp.cnt;
        for(int i=0;i<cnt;i++)
            for(int j=0;j<cnt;j++)
                ans.mat[i][j]=tmp.mat[i][j]+mat[i][j];
        return ans;
    }
};

Matrix a,b,c;

Matrix Pow(Matrix a,unsigned int b)
{
    Matrix r;
    r.init(a.cnt);
    for(int i=0;i<r.cnt;i++)
        r.mat[i][i]=1;
    while(b)
    {
        if(b&1U)r=r*a;
        a=a*a;
        b>>=1;
    }
    return r;
}

Matrix PowSum(Matrix a,unsigned int n)
{
    if(n==1)    return a;
    c=PowSum(a,n>>1);
    if(n&1U)
        return c*(Pow(a,(n>>1)+1))+c+Pow(a,(n>>1)+1);
    return c*Pow(a,(n>>1))+c;
}


ULL Pow(ULL a,unsigned int b)
{
    ULL r=1;
    while(b)
    {
        if(b&1U)r=r*a;
        a=a*a;
        b>>=1;
    }
    return r;
}

ULL PowSum(ULL a,unsigned int n)
{
    if(n==1)    return a;
    if(n&1U)
        return PowSum(a,n>>1)*(Pow(a,(n>>1)+1)+1)+Pow(a,(n>>1)+1);
    return PowSum(a,n>>1)*(Pow(a,(n>>1))+1);
}

int cnt;        //・&#214;&#197;&#228;&#339;úμ&#227;
unsigned int n,m;
int queue[MAXN],head,tail;
int hash[MAXN];      //hash[i]±íê&#376;μúi&#382;&#246;&#339;úμ&#227;ê&#199;μú&#338;&#382;×&#381;ì&#172;


void insert(char *str)
{
    int pos=0;
    for(int i=0;str[i];i++)
    {
        int x=str[i]-'a';
        if(!node[pos].next[x])
        {
            node[++cnt].init();
            node[pos].next[x]=cnt;
        }
        pos=node[pos].next[x];
    }
    node[pos].cnt++;
}

void make_fail()
{
    head=tail=0;
    for(int i=0;i<26;i++)
    {
        if(node[0].next[i])
        {
            queue[tail++]=node[0].next[i];
            node[node[0].next[i]].fail=0;
        }
    }

    while(head<tail)
    {
        int cur=queue[head++];
        int fail=node[cur].fail;
        if(node[fail].cnt)
        {
            node[cur].cnt=1;
        }
        for(int i=0;i<26;i++)
        {
            if(node[cur].next[i])
            {
                queue[tail++]=node[cur].next[i];
                node[node[cur].next[i]].fail=node[fail].next[i];
            }
            else
            {
                node[cur].next[i]=node[fail].next[i];
            }
        }
    }

    int nst=0;      //×&#381;ì&#172;êy

    for(int i=0;i<=cnt;i++)
    {
        if(!node[i].cnt)
        {
            hash[i]=nst++;
        }
    }

    b.init(nst);

    for(int i=0;i<=cnt;i++)
    {
        if(node[i].cnt)
        {
            continue;
        }
        for(int j=0;j<26;j++)
        {
            int tmp=node[i].next[j];
            if(!node[tmp].cnt)
            {
                b.mat[hash[i]][hash[tmp]]++;
            }
        }
    }
    cnt=nst-1;          //cntê&#199;è&#171;&#376;&#214;±&#228;á&#191;&#161;￡&#161;￡
}


ULL solve()
{
    make_fail();

    a.init(b.cnt);

    a.mat[0][0]=1;

    b=PowSum(b,n);
    a=a*b;

    ULL ans=PowSum(26,n);

    for(int i=0;i<a.cnt;i++) ans-=a.mat[0][i];

    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif

    while(scanf("%d %u",&m,&n)==2)
    {
        cnt=0;
        node[cnt].init();
        for(int i=0;i<m;i++)
        {
            char str[100];
            scanf("%s",str);
            insert(str);
        }
#ifndef ONLINE_JUDGE
        printf("%llu\n",solve());
#else
        printf("%I64u\n",solve());
#endif
    }

    return 0;
}
