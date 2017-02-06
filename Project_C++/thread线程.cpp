#include<thread>
#include<iostream>
#include<cstring>
#include<unistd.h>
#include<cstdlib>
using namespace std;
int ti=60;
char str[25]={NULL};
bool pd(char str[])
{
	if(strcmp(str,"123"))
	//return true;
	return false;
	else
	return true;
}
void fun1()
{
	//cout<<"1"<<endl;
	while(ti>0&&!pd(str))
	{
		if(pd(str))
		cout<<"错误！剩余"<<ti<<"秒"<<endl;
		ti--;
		sleep(1);
	}
	if(ti==0)
	exit(-1);
}
void fun2()
{
	//cout<<"2"<<endl;
	while(!pd(str))
	{
		cin>>str;
	}
}
int main()
{
	thread a(fun1);
	thread b(fun2);
	a.join();
//	cout<<"m"<<endl;
	b.join();
	return 0;
}