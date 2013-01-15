#include<cstdio>

#define keyTree (ch[ch[root][1]][0])
#define min(a,b) (a<b?a:b)

const int maxn=200100;
const int INF=1<<28;

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
    int rev[maxn];          //翻转标记
    int sum[maxn];          //区间和

    inline void getmin(int x)
    {
        sum[x]=add[x]+val[x];
        if(ch[x][0])
            sum[x]=min(sum[x],sum[ch[x][0]]);
        if(ch[x][1])
            sum[x]=min(sum[x],sum[ch[x][1]]);
    }
   inline  void push_down(int x)
    {
        if(add[x])
        {
            val[x]+=add[x];
            if(ch[x][0])
            {
                add[ch[x][0]]+=add[x];
                sum[ch[x][0]]+=add[x];
            }
            if(ch[x][1])
            {
                add[ch[x][1]]+=add[x];
                sum[ch[x][1]]+=add[x];
            }
            add[x]=0;
        }
        if(rev[x])  reverseNode(x);         //翻转
    }

    inline void reverseNode(int x)
    {
        int tmp=ch[x][0];
        ch[x][0]=ch[x][1];
        ch[x][1]=tmp;

        rev[ch[x][0]]^=1;
        rev[ch[x][1]]^=1;
        rev[x]=0;
    }
    //sum[x]始终表示以x为根的树的所有结点值的和
    //add[x]只标记了x为根的树表示的区间增加 了 多少
    //查询一个点的值也要查询sum[x]，因为add标记并没有加到val[x]上去
   inline  void push_up(int x)
    {
        sz[x]=1+sz[ch[x][0]]+sz[ch[x][1]];

        getmin(x);
    }

    //在x处新建一个结点，值为c，父亲是fa
    inline void NewNode(int &x,int c,int fa)
    {
        if(top2)    x=ss[--top2];
        else    x=++top1;

        sz[x]=1;
        add[x]=0;
        rev[x]=0;
        ch[x][0]=ch[x][1]=0;       //无左右儿子
        val[x]=sum[x]=c;
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
        add[0]=sum[0]=0;

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
	inline void erase(int x) {		int fa = pre[x];
		int head = 0 , tail = 0;
		for (que[tail++] = x ; head < tail ; head ++) {
			ss[top2 ++] = que[head];
			if(ch[ que[head] ][0]) que[tail++] = ch[ que[head] ][0];
			if(ch[ que[head] ][1]) que[tail++] = ch[ que[head] ][1];
		}
		ch[ fa][ ch[fa][1] == x ] = 0;
		push_up(fa);
	}
    inline void query(int l,int r)
    {
        RotateTo(l-1,superRoot);
        RotateTo(r+1,root);

        printf("%d\n",sum[keyTree]);
    }
    //把[l,r]所有数加c
    inline void update(int l,int r,int c)
    {
        RotateTo(l-1,superRoot);        //l-1在root
        RotateTo(r+1,root);             //r+1在root右儿子

        add[keyTree] += c;
        sum[keyTree] += c;

    }

    //debug用，中序输出树
    void debug() {printf("%d\n",root);Treaval(root);puts("");}
	void Treaval(int x) {
		if(x) {
		    push_down(x);
			Treaval(ch[x][0]);
			printf("结点%2d:左儿子 %2d 右儿子 %2d 父结点 %2d size = %2d ,val = %2d\n",x,ch[x][0],ch[x][1],pre[x],sz[x],val[x]);
			//printf("%d ",val[x]);
			Treaval(ch[x][1]);
		}
	}
	//以上Debug


    ///********以下是自己写的不靠谱函数

    //把区间[l,r]翻转,即[l,r]上的中序遍历反向
    //滚动操作可以变成翻转操作
    //把[l...m,m+1...r]滚动成[m+1...r,l...m]
    //只需要reverse(m+1,r),reverse(l,m),reverse(l,r)
    inline void  reverse(int l,int r)
    {
        RotateTo(l-1,superRoot);
        RotateTo(r+1,root);

        rev[keyTree]^=1; //具体翻转在push_down时调用reverseNode函数
    }

    //把n个数插入l和l+1之间
    inline void insert(int l,int n)
    {
        for(int i=0;i<n;i++)    scanf("%d",&num[i]);
        RotateTo(l,superRoot);
        RotateTo(l+1,root);

        makeTree(keyTree,0,n-1,ch[root][1]);
        push_up(ch[root][1]);
        push_up(root);
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
	scanf("%d",&n);

	spt.init(n);
	scanf("%d",&m);
	while(m --) {
		char op[10];
		scanf("%s",op);
		if(op[0] == 'M') {
		    int l,r;
            scanf("%d %d",&l,&r);
            spt.query(l,r);
		} else if(op[0]=='A'){
		    int l,r,c;
            scanf("%d %d %d",&l,&r,&c);
			spt.update(l,r,c);
		}
		else if(op[0]=='D'){
		    int l;
            scanf("%d",&l);
		    spt.del(l,l);
		}
		else if(op[0]=='I'){
            int l;
            scanf("%d",&l);
            spt.insert(l,1);
		}
		else if(op[0]=='R' && op[3]=='E'){
		    int l,r;
		    scanf("%d %d",&l,&r);
		    spt.reverse(l,r);

		}
		else if(op[0]=='R' && op[3]=='O'){
		    int l,r,t;
		    scanf("%d %d %d",&l,&r,&t);
		    int len=r-l+1;
		    t=t%len;
		    int mid=r-t;

		    spt.reverse(mid+1,r);
		    spt.reverse(l,mid);
		    spt.reverse(l,r);
		}
	}
	return 0;
}
