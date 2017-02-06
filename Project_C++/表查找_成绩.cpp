#include <iostream>
#include <vector>
using namespace std;
int main()
{
	puts((*new std::vector<char *>({"优", "良", "中"}))[getchar()-'A']);
	return 0;
}