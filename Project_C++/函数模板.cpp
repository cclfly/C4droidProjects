#include <iostream>
using namespace std;

template <typename T>
inline T const &max(T const& a,T const& b)
{
	return a>b?a:b;
}

int main()
{
	cout<<::max(7,8)<<endl;
	cout<<::max(8.9,7.5)<<endl;
	
	return 0;
}