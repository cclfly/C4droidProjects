#include <iostream>
#include <thread>
using namespace std;
class A {
	public:
	void run()
	{
		cout<<"running"<<endl;
	}
	void thread()
	{
		for(int i=0;i<5;i++)
		{
			(new std::thread(&A::run,this))->join();
		}
	}
};
int main()
{
	A a;
	a.run();
	thread t1(bind(&A::run,&a));
	thread t2(&A::run,&a);
	t1.join();
	t2.join();
	a.thread();
	return 0;
}