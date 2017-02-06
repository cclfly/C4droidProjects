#include <iostream>
#include <functional>
#include <cstdio>

using namespace std;

template<typename F,typename ...Args>
auto func(F f,Args ...args)
{
	return bind(f,args...);
}

int main()
{
	function<void()> f=bind([](int i){cout<<i<<endl;},7);
	f();
	func(printf,"aaa%d\n",8)();
}