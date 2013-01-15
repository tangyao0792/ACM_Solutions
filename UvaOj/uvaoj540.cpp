#include<iostream>
#include<algorithm>
#include<string.h>
#define NMAX 1000


#include<stdio.h>

using namespace std;

typedef struct Node
{
    int d;
    int team;
    Node* next;
}Node, *pNode;

pNode teamQueue;
pNode lastElement[NMAX];            //指向queue中本team的最后一个元素
pNode lastOfQueue;                  //指向queue的最后一个元素
int teamElement[NMAX][NMAX];
int nCountElement[NMAX];

int search(int a[], int length, int v);

int main()
{
    freopen("in.txt", "r", stdin);
    int nCountTeam;
    int i, j, n, pos;
    const char enq[] = "ENQUEUE";
    const char deq[] = "DEQUEUE";
    const char stp[] = "STOP";
    char input[10];
    pNode temp;
    int nCount = 0;
    while(cin >> nCountTeam)
    {
        if(nCountTeam == 0)
        {
            break;
        }
        nCount++;
        cout << "Scenario #" << nCount << endl;

        memset(teamElement, 0, sizeof(int) * NMAX * NMAX);
        memset(nCountElement, 0, sizeof(int)* NMAX);


        teamQueue = NULL;
        lastOfQueue = teamQueue;

        for(i = 0; i < NMAX; i++)
        {
            lastElement[i] = NULL;
        }

        for(i = 0; i < nCountTeam; i++)
        {
            cin >> nCountElement[i];
            for(j = 0; j < nCountElement[i]; j++)
            {
                cin >> teamElement[i][j];
            }
            sort(teamElement[i], teamElement[i]+nCountElement[i]);
        }
        while(cin >> input)
        {
            if(strcmp(input, stp) == 0)
            {
                break;
            }
            else if(strcmp(input, enq) == 0)
            {
                cin >> n;
                for(i = 0; i < nCountTeam; i++)     //找到n在第i个team
                {
                    pos = search(teamElement[i], nCountElement[i], n);
                    if(pos != -1)
                    {
                        break;
                    }
                }

                temp = new Node;
                temp->d = n;
                temp->team = i;
                temp->next = NULL;
                if(teamQueue == NULL)
                {
                    teamQueue = temp;
                    lastOfQueue = temp;

                    lastElement[i] = temp;
                }
                else if(lastElement[i] == NULL)
                {
                    lastOfQueue->next = temp;   //queue的最后一个
                    lastOfQueue = temp;

                    lastElement[i] = temp;
                }
                else
                {
                    if(lastOfQueue == lastElement[i])//如果找到一个team中的，但还要排在最后
                    {
                        lastOfQueue->next = temp;
                        lastOfQueue = temp;
                    }
                    temp->next = lastElement[i]->next;
                    lastElement[i]->next = temp;
                    lastElement[i] = temp;

                }

            }
            else if(strcmp(deq, input) == 0)
            {
                cout << teamQueue->d << endl;
                if(lastElement[teamQueue->team] == teamQueue)
                {
                    lastElement[teamQueue->team] = NULL;
                }
                teamQueue = teamQueue->next;
            }
        }
        cout << endl;

    }
    return 0;
}

int search(int a[], int length, int v)
{
    int l = 0;
    int r = length - 1;
    int mid = (l+r)/2;
    while(l < r+1)
    {
        if(v == a[mid])
        {
            return mid;
        }
        else if(a[mid] > v)
        {
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
        mid = (l+r)/2;
    }
    return -1;
}
