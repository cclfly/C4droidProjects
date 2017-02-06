#include <iostream>
using namespace std;
int main()
{
	//auto a=[](){cout<<"hello"<<endl;};
	//a();
	([](){cout<<"hello"<<endl;})();
	return 0;
}