#include<iostream>
using namespace std;
void swep(int*fuck,int a)
{
	int temp=0;
	for (int j=0;j<a;j++)
	for(int i=0;i<a-j-1;i++)
	{
		if (fuck[i]<fuck[i+1])
		{
			temp=fuck[i];
			fuck[i]=fuck[i+1];
			fuck[i+1]=temp;
		}
	}
}
int main ()
{
	int n;
	cout<<"请输入数组个数"<<endl;
	cin>>n;
	int *a=new int[n];
	for (int j=0;j<n;j++)
	cin>>a[j];
	swep(a,n);
	for(int i=0;i<n;i++)
	cout<<a[i]<<"  ";
	delete [] a;
}