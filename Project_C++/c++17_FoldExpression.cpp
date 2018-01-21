/// fold expression
/// 展开变长参数模板进行运算
#include <iostream>
using namespace std;

template <typename ...Args>
auto func(Args ...args)
{
	return (args*...);
}

template <typename ...Args>
auto func2(Args ...args)
{
	return (args-...);//(a-(b-c))
}

template <typename ...Args>
auto func3(Args ...args)
{
	return (...-args);//((a-b)-c)
}

template <typename T>
void print(T t)
{
	cout<<t<<"  ";
}
template <typename ...Args>
void func4(Args ...args)
{
	(print(args),...);//用逗号表达式依次调用
}

int main()
{
	cout<<func(1,2.3,4)<<endl;
	cout<<func2(1,2.3,4)<<endl;
	cout<<func3(1,2.3,4)<<endl;
	func4(1,2.3,4);
}