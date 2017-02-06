#include <iostream>
#include <cmath>
using namespace std;
double round(double,int);
int main()
{
	cout<<round(-8.7546743,4)<<endl;
}
double round(double num,int n=0)
{
	return num>0?int(num*pow(10,n)+0.5)/pow(10,n):int(num*pow(10,n)-0.5)/pow(10,n);
}
