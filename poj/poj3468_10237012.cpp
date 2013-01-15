#include<cstdio>

#define keyTree (ch[ch[root][1]][0])

const int maxn=222222;

struct SplayTree
{
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
    int add[maxn];          //对这个区间标记
    long long sum[maxn];          //区间和

   inline  void push_down(int x)
    {
        if(add[x])
        {
            val[x]+=add[x];
            add[ch[x][0]]+=add[x];
            sum[ch[x][0]]+=(long long)add[x]*sz[ch[x][0]];
            add[ch[x][1]]+=add[x];
            sum[ch[x][1]]+=(long long)add[x]*sz[ch[x][1]];
            add[x]=0;
        }
    }
    //sum[x]始终表示以x为根的树的所有结点值的和
    //add[x]只标记了x为根的树表示的区间增加 了 多少
    //查询一个点的值也要查询sum[x]，因为add标记并没有加到val[x]上去
   inline  void push_up(int x)
    {
        sz[x]=1+sz[ch[x][0]]+sz[ch[x][1]];
        sum[x]=add[x]+val[x]+sum[ch[x][0]]+sum[ch[x][1]];
    }

    //在x处新建一个结点，值为c，父亲是fa
    inline void NewNode(int &x,int c,int fa)
    {
        if(top2)    x=ss[--top2];
        else    x=++top1;

        sz[x]=1;
        add[x]=0;
        ch[x][0]=ch[x][1]=0;       //无左右儿子
        val[x]=sum[x]=c;
        pre[x]=fa;
    }

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
        add[0]=sum[0]=0;

        root=top1=top2=0;
        superRoot = 0;
        NewNode(root,-1,superRoot);
        NewNode(ch[root][1],-1,root);

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

        if(pre[x]!=-1)  ch[pre[x]][y==ch[pre[x]][1]]=x;

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

    inline void query(int l,int r)
    {
        RotateTo(l-1,superRoot);
        RotateTo(r+1,root);

        printf("%lld\n",sum[keyTree]);
    }
    //把[l,r]所有数加c
    inline void update(int l,int r,int c)
    {
        RotateTo(l-1,superRoot);        //l-1在root
        RotateTo(r+1,root);             //r+1在root右儿子

        add[keyTree] += c;
        sum[keyTree] += (long long )c*sz[keyTree];

    }
}spt;
inline void readint(int &ret)
{
	char c;
	do {	c = getchar();
	} while(c < '0' || c > '9');
	ret = c - '0';
	while((c=getchar()) >= '0' && c <= '9')
		ret = ret * 10 + ( c - '0' );
}
int main() {

#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif

	int n , m;
	scanf("%d%d",&n,&m);
	spt.init(n);
	while(m --) {
		char op[2];
		scanf("%s",op);
		if(op[0] == 'Q') {
		    int l,r;
		    readint(l),readint(r);
			spt.query(l,r);
		} else {
		    int l,r,c;
		    readint(l),readint(r);

		    scanf("%d",&c);
			spt.update(l,r,c);
		}
	}
	return 0;
}
