#include <stdio.h>
class A{
public:
	A(){
		puts ("fuck1");
	}
	A(const A &a){
		puts ("fuck 2");
	}
	~A(){
		puts ("fuck3");
	}
};
int main(int argc ,char *argv[]){
	A(A());     //啥反应都没有 构造 复制 析构都没有调用
	(A((A()))); //加上括号让编译器认为是对象，而不是调用函数
}