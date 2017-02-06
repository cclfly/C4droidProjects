/*
  *  算法导论
  *  p17 MERGE(A,p,q,r)
  *  p19 MERGE-SORT(A,p,r)
  *  分治法 - 归并排序
  */
#include <iostream>
#include <cmath>
using namespace std;
template < class T > void merge (T a[], int p, int q, int r)
{
    int n1, n2, i, j, k;
    T *L, *R;
    n1 = q - p + 1;
    n2 = r - q;
    L = new T[n1 + 1];
    R = new T[n2 + 1];
    for (i = 0; i < n1; i++)
    {
        L[i] = a[p + i];
    }
    for (j = 0; j < n2; j++)
    {
        R[j] = a[q + j + 1];
    }
    L[n1] = INT_MAX;
    R[n2] = INT_MAX;
    i = 0;
    j = 0;
    for (k = p; k < r + 1; k++)
    {
        if (L[i] <= R[j])
        {
            a[k] = L[i];
            i++;
        }
        else
        {
            a[k] = R[j];
            j++;
        }
    }
    delete[]L;
    delete[]R;
}

template < class T > void merge_sort (T a, int p, int r)
{
    if (p < r)
    {
        int q = floor ((p + r) / 2.0);
        merge_sort (a, p, q);
        merge_sort (a, q + 1, r);
        merge (a, p, q, r);
    }
}

template < class T > void forprintln (T a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " , ";
    }
    cout << "\b\b  " << endl;
}

int main ()
{
    int a[6] = { 42, 2, 57, 36, 9, 45 };
    forprintln (a, 6);
    merge_sort (a, 0, 5);
    forprintln (a, 6);
    return 0;
}