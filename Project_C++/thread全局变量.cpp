#include <iostream>
#include <thread>
using namespace std;
int n=0;
void fun1()
{
	n=1;
	for(int i=0;i<7;i++);
	cout<<n<<endl;
	//for(int i=0;i<199;i++);
}
void fun2()
{
	n=2;
	for(int i=0;i<780;i++);
	cout<<n<<endl;
}
void fun3()
{
	n=3;
	for(int i=0;i<78;i++);
	cout<<n<<endl;
}
int main()
{
	cout<<"main0:"<<n<<endl;
	thread a2(fun1);
	cout<<"main1:"<<n<<endl;
	thread a3(fun2);
	cout<<"main2:"<<n<<endl;
	thread a1(fun3);
	cout<<"main3:"<<n<<endl;
	a1.join();
	cout<<"main4:"<<n<<endl;
	a3.join();
	cout<<"main5:"<<n<<endl;
	a2.join();
	cout<<"main6:"<<n<<endl;
	
	return 0;
}