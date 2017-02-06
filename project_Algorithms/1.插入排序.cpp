/*
 *  算法导论
 *  p14 INSERTION-SORT(A)
 *  插入排序
 */
#include <iostream>
using namespace std;
template <class T>
void insertion_sort(T *a,int n)
{
	int i,j;
	T tmp;
	for(i=1;i<n;i++)
	{
		tmp=a[i];
		j=i-1;
		while(j>=0&&a[j]>tmp)
		{
			a[j+1]=a[j];
			j--;
		}
		a[j+1]=tmp;
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
	insertion_sort(a,6);
	forprintln(a,6);
	return 0;
}