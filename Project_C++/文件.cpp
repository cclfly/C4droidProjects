#include<iostream>
#include<fstream>
#include<ios>
using namespace std;
int main()
{
	fstream file;
	int a=6,b=7,c=8;
	char *ch="gcghfdt";
	file.open("ff",/*ios::in|ios::out|*/ios::binary/*|ios::app*/);
/*	file>>ch;*/
//	file<<"duejdjxndjdid"<<endl;
	file<<a<<b<<ch<<a<<ch<<c;
	int x,y,z;
	char *str;
	file>>x>>y>>str>>x>>str>>z;
	cout<<a<<b<<c<<ch<<endl;
	cout<<x<<y<<z<<str<<endl;
	file.close();
}