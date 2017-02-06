#include <iostream>
#include <vector>
using namespace std;
int main()
{
	//puts((*new std::vector<char *>({"优", "良", "中"}))[getchar()-'A']);
	puts((std::vector<const char *>({"优", "良", "中"}))[([](int a){return a-'A';})(getchar())]);
	return 0;
}