#include<sstream>
using std::stringstream;
using std::endl;

int main()
{
	int i = 0;
	stringstream *y=new stringstream();
	while (1)
	{
		*y << i++ << endl;
	}
}