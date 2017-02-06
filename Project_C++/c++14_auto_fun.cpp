#include <iostream>
using namespace std;
auto fun(auto);
int main()
{
	auto str="Hello world !";
	cout<<str<<endl;
	//int a=str;
    cout<<fun(str)<<endl;
	return 0;
}
auto fun (auto a)
{
	return a;
}