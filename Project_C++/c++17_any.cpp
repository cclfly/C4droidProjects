#include <iostream>
#include <any>
using namespace std;

int main()
{
	any a=[](){cout<<"Hello,World!"<<endl;};
	a();
}