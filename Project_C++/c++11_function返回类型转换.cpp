#include <iostream>
#include <functional>

class A{
public:
    virtual void func(){
    	std::cout<<"A";
    }
};

class B : public A {
public:
    virtual void func(){
    	std::cout<<"B";
    }
};

B* func1() {return new B();}
B func2() {return B();}

int main()
{
	std::function<A*()>fn1(func1);
	fn1()->func();
	std::function<A()>fn2(func2);
	fn2().func();
}