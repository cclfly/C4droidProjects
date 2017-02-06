#include <iostream>
using namespace std;
/*
 * c++11提供了函数类型后置的写法
 * 能使用函数参数实例来推导返回类型
 */
template <typename T1, typename T2>
auto func_cpp11(T1 t1, T2 t2)
    -> decltype(t1+t2)
{
	return t1+t2;
}

/*
 * c++14允许直接使用返回值为auto，
 * 能直接推导返回值类型
 */
template <typename T1, typename T2>
auto func_cpp14(T1 t1, T2 t2)
{
	return t1+t2;
}

int main()
{
	cout << func_cpp11(1,2) << endl;
	cout << func_cpp14(3,4) << endl;
	return 0;
}