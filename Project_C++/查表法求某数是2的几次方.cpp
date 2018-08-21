#include <map>
std::map<std::uint32_t,std::uint8_t> log2{
	{0b00000000000000000000000000000001,0},
	{0b00000000000000000000000000000010,1}
};

#include <iostream>
using namespace std;
int main()
{
	cout<<int(log2[1])<<endl;
	return 0;
}