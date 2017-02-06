#include <iostream>
#include <cstdarg>
using namespace std;
int main()
{
	[](int n,...){
		va_list ap;//一个参数列表
		va_start(ap,n);//初期化列表(n个)
		int tmp;
		for (int i=0;i<n;i++)
		{
			tmp=va_arg(ap,int);//int化ap的指针的值
			cout<<tmp<<endl;
		}
		va_end(ap);//善后
	}(5,6,3,5,3,4);
}