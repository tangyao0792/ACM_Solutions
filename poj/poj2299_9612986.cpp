#include<iostream>

using namespace std;
__int64 count;
void MergeSort(__int64 a[],__int64 first, __int64 last, __int64 p[]);

int main()
{
    __int64 n;
    while(cin >> n && n != 0)
    {
        __int64 *a = new __int64[n];
        __int64 *p = new __int64[n];
        for(__int64 i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        count = 0;
        MergeSort(a,0 ,n-1, p);
        cout << count << endl;

        delete []a;
        delete []p;
    }
    return 0;
}

void MergeSort(__int64 a[], __int64 first, __int64 last, __int64 p[])
{
    if(first < last)
    {
        MergeSort(a, first, (first+last)/2,p);
        MergeSort(a, (first+last)/2+1, last, p);

        __int64 mid = (first + last) / 2;
        __int64 i = first;
        __int64 j = mid+1;
        __int64 k = first;
        for(; i < last +1; i++)
        {
            p[i] = a[i];
        }
        i = first;

        while(i < mid+1 && j < last+1)
        {
            while(i < mid+1 && j < last+1)
            {
                if(p[i] < p[j])
                {
                    a[k++] = p[i++];
                }
                else
                {
                    a[k++] = p[j++];
                    count += mid - i +1;        //i组剩得数都算
                }
            }

            while(i < mid+1)
            {
                a[k++] = p[i++];
            }

            while(j < last+1)
            {
                a[k++] = p[j++];
            }
        }


    }
}
