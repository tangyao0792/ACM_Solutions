#include<iostream>
#include<stdlib.h>
using namespace std;

int cmp(const void *a, const void *b);

int main()
{
    int *p;
    int n;
    cin >> n;
    p = new int[n];
    for(int i = 0; i < n; i++)
    {
        cin >> p[i];
    }
    qsort(p, n, sizeof(int),cmp);

    cout << p[n/2] << endl;

    return 0;
}

int cmp(const void *a, const void *b)
{
    return *(int*)a - *(int *)b;
}
