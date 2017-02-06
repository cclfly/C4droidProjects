#include<iostream>
using namespace std;

int (*(func(int n)))(int)
{
	cout<<n<<' ';
	return (int(*)(int))func;
}

int main()
{
	auto f=(int(*((*)(int)))(int))func(1)(2);
	f(3)(4);
}