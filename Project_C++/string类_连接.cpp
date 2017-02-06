#include<iostream>
#include<cstring>
using namespace std;
int main()
{
	string str1="udjduf",str2="heusisc";
	char *ch1="hdbch",*ch2="jujdieif";
	string st1=str1+str2;
	string st2=(string)ch1+(string)ch2;
	cout<<st1<<endl;
	cout<<st2<<endl;
}