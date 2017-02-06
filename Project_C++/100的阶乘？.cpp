#include<iostream>
using namespace std;
int main()
{
	 //long long jie=1;
	 long double jie;
	int i=1;
	for(int j=1;j<100;j++)
	{
		jie=1;
		for(i=1;i<=j;i++)
	jie*=i;
	cout<<j<<"\t\t"<<jie<<endl;
	}
}