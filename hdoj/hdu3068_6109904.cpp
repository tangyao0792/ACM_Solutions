/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

const int MAXN = 110020;
char s[MAXN];
char str[MAXN*2];
int p[MAXN*2];
int len,n;


int manacher(char *s) 
{  
    len=strlen(s);
    str[0]='@';
    str[1]='#';
    n=2;
    for(int j=0;j<len;j++)
    {
        str[n++]=s[j];
        str[n++]='#';
    }
    str[n]=0;

    int mx = 0;  
    int id;  
    for (int i = 1; i < n; i++) 
    {
        if (mx > i)
        { 
            p[i] = min(p[2*id - i], mx - i); 
        }
        else 
            p[i] = 1;  
        for (; str[i - p[i]] == str[i + p[i]]; p[i]++)
            ;
        if (p[i] + i > mx)
        {  
            mx = p[i] + i;  
            id = i;  
         } 
     } 
     int ans=0;
     for(int i=1;i<n;i++)
     {
         ans=max(ans,p[i]);
     }
     return ans-1;
}  

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    while(~scanf("%s",s))
    {
        printf("%d\n",manacher(s));    
    }
    return 0;
}
