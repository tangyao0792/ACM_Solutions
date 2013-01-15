/*
 *   Author: Tangyao
 *   Email:  tangyao0792@gmail.com
 *   tangyao0792.github.com
 */
#include<cstdio>
#include<cstring>

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif

    char str[110];

    while(scanf("%s",str))
    {
        if(str[0]=='#') break;
        bool flag=false;
        int nLen=strlen(str);
        int half=nLen/2;
        for(int i=0;!flag && i<nLen;i++)
        {
            bool is=true;
            for(int j=1;j<=half;j++)
            {
                if(str[(i+j)%nLen] != str[(i-j+nLen)%nLen])
                {
                    is=false;
                    break;
                }
            }
            if(is)
            {
                printf("YES %d\n",i);
                flag=true;
                break;
            }
        }

        if(!flag)printf("NO\n");
    }

    return 0;
}
