#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

typedef struct
{
    char str[30];
    int from;
    int to;
}E;
int s[1010],sp,v[1010];
E e[1010];
bool in[26],b1,b2;
int flag[26],p[26];
int n;

void Euler(int cnt)
{
    for(int i=0;i<n;i++)
    {
        if(!v[i]&&e[cnt].to==e[i].from)
        {
            v[i]=1;
            Euler(i);
            s[sp++]=i;
        }
    }
}

int find(int x){return p[x]==-1?x:(p[x]=find(p[x]));}

int judge()     //0无欧拉路，1欧拉路，2欧拉回路
{
    int k;
    for(int i=0;i<26;i++)
        if(in[i])
        {
            k=find(i);
            break;
        }
    for(int i=0;i<26;i++)
        if(in[i]&&k!=find(i))
            return 0;

    bool b=true;
    for(int i=0;i<26;i++)
        if(flag[i]!=0)
            b=false;
    if(b)
        return 2;

    bool b1=false,b2=false;
    for(int i=0;i<26;i++)
    {
        if(flag[i]==-1)
        {
            if(b1)
                return 0;
            else
                b1=true;
        }
        else if(flag[i]==1)
        {
            if(b2)
                return 0;
            else
                b2=true;
        }
        else if(flag[i]!=0)
            return 0;
    }
    if(b1&&b2)
        return 1;
    return 0;
}

bool comp(E a, E b){return strcmp(a.str,b.str)<0;}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("A.1.dat", "r", stdin);
    freopen("a.out","w",stdout);
#endif
    int nCase;
    scanf("%d",&nCase);
    while(nCase--)
    {
        memset(e,0,sizeof(e));
        memset(flag,0,sizeof(flag));
        memset(p,-1,sizeof(p));
        memset(in,false,sizeof(in));
        memset(v,0,sizeof(v));

        scanf("%d",&n);
        for(int i=0;i<n;i++)
        {
            scanf("%s",e[i].str);

            e[i].from=e[i].str[0]-'a';
            flag[e[i].from]--;
            e[i].to=e[i].str[strlen(e[i].str)-1]-'a';
            flag[e[i].to]++;
            in[e[i].from]=true;
            in[e[i].to]=true;

            int x=find(e[i].from),y=find(e[i].to);
            if(x!=y)
                p[x]=y;
        }
        sort(e,e+n,comp);
        int ans=judge();
        if(ans==0)
        {
            printf("***\n");
            continue;
        }
        else if(ans==1)
        {
            for(int i=0;i<n;i++)
                if(flag[e[i].from]==-1)
                {
                    sp=0;
                    v[i]=1;
                    Euler(i);
                    s[sp++]=i;
                    break;
                }
        }
        else
        {
            sp=0;v[0]=1;
            Euler(0);
            s[sp++]=0;
        }
        printf("%s",e[s[sp-1]].str);
        for(int i=sp-2;i>=0;i--)
            printf(".%s",e[s[i]].str);
        printf("\n");


    }
    return 0;
}
