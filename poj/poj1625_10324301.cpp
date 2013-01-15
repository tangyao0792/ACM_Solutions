#include<iostream>
#include<cstring>
#include<cstdio>
#include<map>

using namespace std;

const int maxn = 100;
const int MAXN = 510;


class BigN
{
public:
    int len;
    int s[maxn];
    BigN()
    {
        len = 1;
        memset(s, 0, sizeof(s));
    }
    void init()
    {
        len=1;
        memset(s,0,sizeof(s));
    }
    BigN(int num)
    {
        *this = num;
    }
    BigN(const char* num)
    {
        *this = num;
    }

    string toString()const
    {
        string res = "";
        for(int i = 0; i < len; i++)
        {
            res = (char)(s[i] + '0') + res;
        }
        if(res == "")
        {
            res = "0";
        }
        return res;
    }
    BigN operator = (const char *num)
    {
        len = strlen( num);
        for(int i = len - 1; i > -1 ;i--)
        {
            s[len-i-1] = num[i] - '0';
        }
        return *this;
    }
    BigN operator = (int num)
    {
        char s[maxn];
        sprintf(s, "%d",num);
        *this = s;
        return *this;
    }

    BigN operator + (const BigN& b) const
    {
        BigN c;
        int max;
        if(b.len > this->len)
        {
            max = b.len;
        }
        else
        {
            max = this->len;
        }
        int g = 0;
        int i;
        for(i = 0; i < max || g > 0; i++)
        {
            int temp = (*this).s[i] + b.s[i] + g;
            c.s[i] = temp % 10;
            g = temp / 10;
        }
        c.len = i;
        return c;
    }

    BigN operator * (const BigN &b )const
    {
        BigN d;
        int i, j;
        int g = 0;
        for(i = 0; i < b.len; i++)
        {
            for(j = 0; j < (*this).len || g != 0; j++)
            {
                int temp = d.s[i+j]+(*this).s[j] * b.s[i] + g;
                d.s[i+j] = temp % 10;
                g = temp / 10;
            }
        }
        d.len = i + j - 1;

        return d;
    }

};
ostream& operator <<(ostream &out, BigN &x)
{
    out << x.toString();
    return out;
}
istream& operator >>(istream &in, BigN &x)
{
    string s;
    in >> s;
    x = s.c_str();
    return in;
}


struct Node
{
    int next[60];
    int fail,cnt;
    void init()
    {
        cnt=fail=0;
        memset(next,0,sizeof(next));
    }
}node[MAXN];

int cnt;        //分配节点
int n,m,k;
int queue[MAXN],head,tail;
int hash[MAXN];      //hash[i]表示第i个节点是第几状态

map<char,int> char_to_int;

int g[MAXN][MAXN];

BigN ans[60][300];

void insert(char *str)
{
    int pos=0;
    for(int i=0;str[i];i++)
    {
        int x=char_to_int[str[i]+200];
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
    for(int i=0;i<k;i++)
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
        for(int i=0;i<k;i++)
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

    int nst=0;      //状态数

    for(int i=0;i<=cnt;i++)
    {
        if(!node[i].cnt)
        {
            hash[i]=nst++;
        }
    }
    for(int i=0;i<=cnt;i++)
    {
        if(node[i].cnt)
        {
            continue;
        }
        for(int j=0;j<k;j++)
        {
            int tmp=node[i].next[j];
            if(!node[tmp].cnt)
            {
                g[hash[i]][hash[tmp]]++;
            }
        }
    }
    cnt=nst;
}


void solve()
{
    memset(g,0,sizeof(g));
    make_fail();

    for(int i=0;i<=n;i++)
        for(int j=0;j<cnt;j++)
            ans[i][j].init();
    ans[0][0]=1;
    BigN tmp;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<cnt;j++)
        {
            for(int l=0;l<cnt;l++)
            {
                if(g[l][j])
                {
                    tmp=g[l][j];
                    ans[i][j]=ans[i][j]+ans[i-1][l]*tmp;
                }
            }
        }
    }


    BigN answer;
    answer.init();
    answer=0;
    for(int i=0;i<cnt;i++)
    {
        //cout<<ans[n][i]<<" ."<<answer<<" ";
        answer = answer+ans[n][i];
    }
    cout<<answer<<endl;
}


int main()
{

#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif

    while(scanf("%d %d %d",&k,&n,&m)==3)
    {
        cnt=0;
        node[cnt].init();
        char str[100];
        char_to_int.clear();
        gets(str);
        gets(str);
        for(int i=0;i<k;i++)
        {
            char_to_int[str[i]+200]=i;
        }
        for(int i=0;i<m;i++)
        {
            gets(str);
            insert(str);
        }
        solve();
    }


    return 0;
}
