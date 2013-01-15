#include<cstdio>
#include<cstring>

const int MAXN=10200;
char str[MAXN];

int n;

struct sanode
{

	sanode * ch[26];
	sanode * f;
	int ml; //the longest way to arrive this state
	int pos;    //the state can represent which suffix
	inline void init()
	{

		for(int i=0;i<26;i++)
			ch[i]=NULL;
	}
}pool[MAXN*2],*tail,*init;
int tot;

void add(int c,int len)
{

	sanode *p= tail;
	sanode *np=&pool[++tot];
	np->init();
	np->ml = len;
	np->pos=len;
	for(; p!=NULL && p->ch[c] == NULL; p=p->f)
		p->ch[c]=np;
	tail=np;
	if(p==NULL)
		np->f=init;
	else
	{

		if(p->ch[c]->ml == p->ml+1)
			np->f=p->ch[c];
		else
		{

			sanode *q = p->ch[c], *r = &pool[++tot];
			*r = *q;
			r->ml = p->ml+1;
			r->pos=p->ch[c]->pos;

			q->f = np->f = r;
			for(; p!=NULL && p->ch[c] == q; p= p->f)
				p->ch[c]=r;
		}
	}
}

inline void build(char *s)
{

	tot=0;
	init=&pool[0];
	init->init();
	tail=init;
	n=1;
	for(int i=0;s[i]!=0;i++,n++)
	{
		add(s[i]-'a',n);
	}
	for(int i=0;s[i]!=0;i++,n++)
	{
		add(s[i]-'a',n);
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%s",str);
		build(str);
		sanode *cur=init;
		n/=2;
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<26;j++)
			{
				if(cur->ch[j])
				{
					cur=cur->ch[j];
					break;
				}
			}
		}
		int ans=cur->pos%n;

		printf("%d\n",ans+1);
	}
	return 0;
}
