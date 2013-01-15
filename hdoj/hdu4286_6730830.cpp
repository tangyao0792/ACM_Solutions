/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

#define keyTree (ch[ch[root][1]][0])
#define min(a,b) (a<b?a:b)

const int maxn=1000010;
const int INF=1<<28;
int ff;

inline bool read(int &num) {
    char in;bool IsN=false;
    in=getchar();
    if(in==EOF) return false;
    while(in!='-'&&(in<'0'||in>'9')) in=getchar();
    if(in=='-'){
        IsN=true;num=0;} else num=in-'0';
    while(in=getchar(),in>='0'&&in<='9') num*=10,num+=in-'0';
    if(IsN) num=-num;
    return true;
}
struct SplayTree
{
    int stk[maxn],sp;    //used for output
    int sz[maxn];   //sz[i]以i为根的树的结点数
    int ch[maxn][2]; //左右儿子
    int pre[maxn];  //爹
    int root,top1,top2;     //top1,top2用来分配内存
    int superRoot;          //splay树的根
    int ss[maxn],que[maxn];
    //ss为内存池,ch[i]数组并不是按照儿子是父亲编号的两倍分配的
    //ss[i]=j表示内存池中第i个点是ch[j]，如果i不在使用，说明ch[j]为可用结点

    int num[maxn];       //初始数组的值
    int val[maxn];          //结点的值
    int rev[maxn];          //翻转标记



    inline void push_down(int x)
    {
        if(rev[x])
        {
            int tmp=ch[x][0];
            ch[x][0]=ch[x][1];
            ch[x][1]=tmp;

            rev[ch[x][0]]^=1;
            rev[ch[x][1]]^=1;
            rev[x]=0;
        }

    }
    //sum[x]始终表示以x为根的树的所有结点值的和
    //add[x]只标记了x为根的树表示的区间增加 了 多少
    //查询一个点的值也要查询sum[x]，因为add标记并没有加到val[x]上去
   inline  void push_up(int x)
    {
        sz[x]=1+sz[ch[x][0]]+sz[ch[x][1]];

    }

    //在x处新建一个结点，值为c，父亲是fa
    inline void NewNode(int &x,int c,int fa)
    {
        if(top2)    x=ss[--top2];
        else    x=++top1;

        sz[x]=1;
        rev[x]=0;
        ch[x][0]=ch[x][1]=0;       //无左右儿子
        val[x]=c;
        pre[x]=fa;
    }

    //以num[l...r]建一棵树
   inline  void makeTree(int &x,int l,int r,int fa)
    {
        if(l>r) return;
        int m=(l+r)>>1;
        NewNode(x,num[m],fa);

        makeTree(ch[x][0],l,m-1,x);
        makeTree(ch[x][1],m+1,r,x);

        push_up(x);
    }

   inline  void init(int n)
    {
        ch[0][0]=ch[0][1]=pre[0]=sz[0]=0;

        root=top1=top2=0;
        superRoot = 0;
        NewNode(root,-INF,superRoot);
        NewNode(ch[root][1],INF,root);

        for(int i=0;i<n;i++)    scanf("%d",&num[i]);

        makeTree(ch[ch[root][1]][0],0,n-1,ch[root][1]);

        push_up(ch[root][1]);
        push_up(root);
    }

    // f==1表示x是左儿子

    inline void Rotate(int x,int f)
    {
        int y=pre[x];
        push_down(y);
        push_down(x);

        ch[y][!f]=ch[x][f];     //y

        pre[ch[x][f]]=y;        //ch
        ch[x][f]=y;

        pre[x]=pre[y];          //pre x
        pre[y]=x;               //pre y

        if(pre[x]!=superRoot)  ch[pre[x]][y==ch[pre[x]][1]]=x;

        push_up(y);
        push_up(x);
    }

    //把pre[x]结点splay到goal处
    inline void Splay(int x,int goal)
    {
        push_down(x);
        while(pre[x]!=goal)
        {
            if(pre[pre[x]]==goal)
            {
                Rotate(x,ch[pre[x]][0]==x);
            }
            else
            {
                int y=pre[x];int z=pre[y];
                int f=(ch[z][0]==y);
                if(ch[y][f]==x)     //之
                {
                    Rotate(x,!f);Rotate(x,f);
                }
                else
                {
                    Rotate(y,f);Rotate(x,f);
                }
            }
        }
        push_up(x);
        if(goal==superRoot)    root=x;
    }

    //把第k位移到goal位置处
    //k位可以通过sz[k]确定
    //先找到第k位，再splay
    inline void RotateTo(int k,int goal)
    {
        int x=root;
        push_down(x);
        while(k!=sz[ch[x][0]])
        {
            if(k<sz[ch[x][0]])
            {
                x=ch[x][0];
            }
            else
            {
                k-=(sz[ch[x][0]]+1);
                x=ch[x][1];
            }
            push_down(x);
        }
        Splay(x,goal);
    }
    //把以x为祖先结点的树删掉放进内存池,回收内存
    //que队列用于bfs
    inline void erase(int x) {        int fa = pre[x];
        int head = 0 , tail = 0;
        for (que[tail++] = x ; head < tail ; head ++) {
            ss[top2 ++] = que[head];
            if(ch[ que[head] ][0]) que[tail++] = ch[ que[head] ][0];
            if(ch[ que[head] ][1]) que[tail++] = ch[ que[head] ][1];
        }
        ch[ fa][ ch[fa][1] == x ] = 0;
        push_up(fa);
    }

    //以上Debug


    ///********以下是自己写的不靠谱函数

    //把区间[l,r]翻转,即[l,r]上的中序遍历反向
    //滚动操作可以变成翻转操作
    //把[l...m,m+1...r]滚动成[m+1...r,l...m]
    //只需要reverse(m+1,r),reverse(l,m),reverse(l,r)
    inline void  reverse(int l,int r)
    {
        if(l>r)
        {
            int tmp=l;
            l=r;
            r=tmp;
        }
        RotateTo(l-1,superRoot);
        RotateTo(r+1,root);

        rev[keyTree]^=1; //具体翻转在push_down时调用reverseNode函数
    }

    //把n个数插入l和l+1之间
    inline void insert(int l,int x)
    {
//        for(int i=0;i<n;i++)    scanf("%d",&num[i]);
        num[0]=x;
        int n=1;
        RotateTo(l,superRoot);
        RotateTo(l+1,root);

        makeTree(keyTree,0,n-1,ch[root][1]);
        push_up(ch[root][1]);
        push_up(root);
    }
    void print()
    {
        sp=0;
        int cur=root;
        while(cur)
        {
            stk[sp++]=cur;
            push_down(cur);
            cur=ch[cur][0];
        }
        int ff=0;
        while(sp>0)
        {
            cur=stk[--sp];
            if(val[cur]!=INF && val[cur]!=-INF)
            {
                if(ff)    printf(" ");
                ff++;
                printf("%d",val[cur]);
            }
            push_down(cur);
            cur=ch[cur][1];
            while(cur)
            {
                stk[sp++]=cur;
                push_down(cur);
                cur=ch[cur][0];
            }
        }
    }


    //删除区间[l,r],r后的所有数编号前移
    //a1,a2,a3,a4,a5,a6 删除[3,4]的区间
    //a1,a2,a3',a4'     其中a3'就是a5，a4'就是a6
    inline void del(int l,int r)
    {
        RotateTo(l-1,superRoot);
        RotateTo(r+1,root);

        erase(keyTree);
    }
}spt;

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    int n , m;
    int t;
    scanf("%d",&t);
    char op[55],str[55],c;
    int x;

    while(t--)
    {

        scanf("%d",&n);

        spt.init(n);
//        spt.print();
//        puts("");


        int l,r;
        scanf("%d %d",&l,&r);
        scanf("%d",&m);

        while(m--)
        {
//            scanf("%s",op);
            while(true)
            {
                gets(str);
                if(strlen(str))break;
            }

            sscanf(str,"%s",op);
            if(strcmp(op,"MoveLeft")==0)
            {

                sscanf(str,"%s %c",op,&c);
                if(c=='L')  l--;
                else r--;
            }
            else if(strcmp(op,"MoveRight")==0)
            {
                sscanf(str,"%s %c",op,&c);
                if(c=='L')  l++;
                else r++;
            }
            else if(strcmp(op,"Insert")==0)
            {
                sscanf(str,"%s %c %d",op,&c,&x);
                if(c=='L')
                {
                    spt.insert(l-1,x);
                    r++;
                }
                else
                {
                    spt.insert(r,x);
                    r++;
                }
            }
            else if(strcmp(op,"Delete")==0)
            {
                sscanf(str,"%s %c",op,&c);
                if(c=='L')
                {
                    spt.del(l,l);
                    r--;
                }
                else
                {
                    spt.del(r,r);
                    r--;
                }
            }
            else if(strcmp(op,"Reverse")==0)
            {
                spt.reverse(l,r);
            }
//            printf("%s        %d    %d\n",str,l,r);
//            ff=0;
//            spt.print();
//            puts("");
//            puts("");
        }
        ff=0;
        spt.print();
        puts("");
    }

    return 0;
}
