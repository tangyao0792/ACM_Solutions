#include<cstdio>
#include<iostream>
#include<cstring>

using namespace std;

int n;
int p[26],in[26];
bool v[26];
char tmp[1010];

int find(int x){return p[x]==-1?x:(p[x]=find(p[x]));}

bool judge()
{
    int k;
    for(k=0;k<26;k++)   if(v[k])break;

    k=find(k);

    for(int i=0;i<26;i++)
        if(v[i]&&k!=find(i))
            return false;
    bool allZero=true;
    for(int i=0;i<26;i++)
        if(v[i]&&in[i]!=0)
        {
            allZero=false;
            break;
        }
    if(allZero) return true;

    bool b1=false,b2=false;
    for(int i=0;i<26;i++)if(v[i])
    {
        if(in[i]==-1)
        {
            if(b1)
                return false;
            else
                b1=true;
        }
        else if(in[i]==1)
        {
            if(b2)
                return false;
            else
                b2=true;
        }
        else if(in[i]==0)
        {

        }
        else
            return false;
    }
    if(b1&&b2)  return true;
    return false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int nCase;
    scanf("%d", &nCase);
    while(nCase--)
    {
        memset(v,false,sizeof(v));
        memset(p,-1,sizeof(p));
        memset(in,0,sizeof(in));
        scanf("%d",&n);
        for(int i=0;i<n;i++)
        {
            scanf("%s",tmp);
            int nLen=strlen(tmp);
            int f=tmp[0]-'a';
            int l=tmp[nLen-1]-'a';

            v[f]=true;
            v[l]=true;
            in[f]--;
            in[l]++;

            int x=find(f);
            int y=find(l);
            if(x!=y)
                p[x]=y;
        }
        if(judge())
            printf("Ordering is possible.\n");
        else
            printf("The door cannot be opened.\n");
    }
    return 0;
}
