#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
vector<string> mySplit(string str,char ch=' ')
{
	//cout<<str<<endl;
	vector<string> astr;
	string tmp;
	astr.push_back(str);
	stringstream ss(str);
	char tm;
	while (getline(ss,tmp,ch))
	{
		//cout<<tmp<<endl;
		astr.push_back(tmp);
	}
	return astr;
}
int main()
{
	cout<<mySplit("hxg gdhdh sh",'g')[3]<<endl;
	return 0;
}