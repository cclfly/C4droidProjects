#include <iostream>
#include <unistd.h>
#include "MyThreadPool.hpp"
using namespace std;

int main()
{
	MyThreadPool<4> tp;
	tp.add([](){cout<<6<<endl;});
	tp.add([](){cout<<7<<endl;});
	sleep(3);
	return 0;
}