typedef int* pint;
#include <iostream>
using namespace std;
int main()
{
	int a=5;
	pint p=&a,p2=&a;
	//cout.setf(ios_base::showbase);
	cout<<hex<<showbase<<int(p)<<endl
	        <<oct<<showbase<<int(p2)<<endl;
}