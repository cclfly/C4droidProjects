/*
 *  算法导论
 *  p16 2.2-2 SELECT-SORT(A)
 *  选择排序
 */
#include <iostream>
using namespace std;
template <class T>
void swap(T *a,T *b)
{
	T t=*a;
	*a=*b;
	*b=t;
}
template <class T>
void select_sort(T *a,int n)
{
	register int i,j,k,min;
	for (i=0;i<n-1;i++)
	{
		min=i;
		for (j=i+1;j<n;j++)
		{
			if (a[min]>a[j])
			{
				min=j;
			}
		}
		if (min!=i)
		{
			swap(&a[i],&a[min]);
		}
	}
}
template <class T>
void forprintln(T a[],int n)
{
	for(int i=0;i<n;i++)
	{
		cout<<a[i]<<" , ";
	}
	cout<<"\b\b  "<<endl;
}
int main()
{
	int a[6]={42,2,57,36,9,45};
	forprintln(a,6);
	select_sort(a,6);
	forprintln(a,6);
	return 0;
}