#include <iostream>
#include <unistd.h>
using namespace std;
int main()
{
	cout<<fork()<<endl;
	cout<<"1"<<endl;
	cout<<fork()<<endl;
	cout<<"2"<<endl;
}