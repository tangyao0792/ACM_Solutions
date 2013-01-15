#include<iostream>
#include<cstring>
#include<algorithm>

#ifndef ONLINE_JUDGE
    #include<cstdio>
#endif

using namespace std;

#define MAX 121000
#define MAXHASHSIZE 10000019

char list[MAX][30];
int head[MAXHASHSIZE], next[MAX];
char answer[MAX][30];
int sortAnswer[MAX];

void insert_to_table(int cnt);
int hash(char *p);
int look_up(char *p);
bool comp(int a, int b);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int cnt = 1;
    int ans = 0;
    while(cin >> list[cnt])
    {
        insert_to_table(cnt);
        cnt++;
    }
    int i, nLen, j, t;
    char temp[30];
    for(i = 1; i < cnt; i++)
    {
        nLen = strlen(list[i]);
        strcpy(temp, list[i]);
        for(j = 1; j < nLen; j++)
        {
            t = temp[j];
            temp[j] = '\0';
            if( look_up(temp) == 1 && look_up(list[i]+j) == 1)
            {
                sortAnswer[ans] = ans;
                strcpy(answer[ans++], list[i]);

                break;
            }
            temp[j] = t;
        }
    }

    sort( sortAnswer+0, sortAnswer + ans, comp);

    for(i = 0; i < ans; i++)
    {
        cout << answer[sortAnswer[i]] << endl;
    }

    return 0;
}

bool comp(int a, int b)
{
    if(strcmp(answer[a], answer[b]) < 0)
    {
        return true;
    }
    return false;
}

int look_up(char *p)
{
    int h = hash(p);
    int u = head[h];
    while( u != 0)
    {
        if(strcmp(p, list[u]) == 0)
        {
            return 1;
        }
        u = next[u];
    }
    return 0;
}

void insert_to_table(int cnt)
{
    int h = hash(list[cnt]);
    next[cnt] = head[h];
    head[h] = cnt;
}

int hash(char *p)
{
    int nLen = strlen(p);
    int i, n = 0;
    for(i = 0; i < nLen; i++)
    {
        n = n * 31 +p[i];
    }
    return (n & 0x7FFFFFFF) % MAXHASHSIZE;
}
//int hash(char *str)
//{
//    int seed=31,v=0;
//    while(*str)
//    {
//        v=v*seed+*(str++);
//    }
//    return (v&0x7FFFFFFF)%10000019;
//}
//}

//#include<iostream>
//#include<cstring>
//#include<algorithm>
//
//#ifndef ONLINE_JUDGE
//    #include<cstdio>
//#endif
//
//using namespace std;
//
//#define MAX 121000
//#define MAXHASHSIZE 10000019
//
//typedef struct
//{
//    char w[30];
//}Answer;
//
//char list[MAX][30];
//int head[MAXHASHSIZE], next[MAX];
//Answer answer[MAX];
//
//void insert_to_table(int cnt);
//int hash(char *p);
//int look_up(char *p);
//bool comp(Answer a, Answer b);
//
//int main()
//{
//#ifndef ONLINE_JUDGE
//    freopen("in.txt", "r", stdin);
//#endif
//    int cnt = 1;
//    int ans = 0;
//    while(cin >> list[cnt])
//    {
//        insert_to_table(cnt);
//        cnt++;
//    }
//    int i, nLen, j, t;
//    char temp[30];
//    for(i = 1; i < cnt; i++)
//    {
//        nLen = strlen(list[i]);
//        strcpy(temp, list[i]);
//        for(j = 1; j < nLen; j++)
//        {
//            t = temp[j];
//            temp[j] = '\0';
//            if( look_up(temp) == 1 && look_up(list[i]+j) == 1)
//            {
//                strcpy(answer[ans++].w, list[i]);
//                break;
//            }
//            temp[j] = t;
//        }
//    }
//
//    sort( answer+0, answer + ans, comp);
//
//    for(i = 0; i < ans; i++)
//    {
//        cout << answer[i].w << endl;
//    }
//
//    return 0;
//}
//
//bool comp(Answer a, Answer b)
//{
//    if(strcmp(a.w, b.w) < 0)
//    {
//        return true;
//    }
//    return false;
//}
//
//int look_up(char *p)
//{
//    int h = hash(p);
//    int u = head[h];
//    while( u != 0)
//    {
//        if(strcmp(p, list[u]) == 0)
//        {
//            return 1;
//        }
//    }
//    return 0;
//}
//
//void insert_to_table(int cnt)
//{
//    int h = hash(list[cnt]);
//    int u = head[h];
//    while( u != 0)
//    {
//        u = next[u];
//    }
//    next[cnt] = head[h];
//    head[h] = cnt;
//}
//
//int hash(char *p)
//{
//    int nLen = strlen(p);
//    int i, n = 0;
//    for(i = 0; i < nLen; i++)
//    {
//        n = n * 31 + (p[i] - 'a' + 1);
//    }
//    return (n & 0x7FFFFFFF) % MAXHASHSIZE;
//}
