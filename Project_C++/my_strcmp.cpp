#include<iostream>
using namespace std;
int my_strcmp(char*a,char*b)
{
	int i;
	for(i=0;a[i]!='\0'||b[i]!='\0';i++)
	{
		if(a[i]!=b[i])
		return a[i]-b[i];
	}
	return 0;
}
int main()
{
	char *a=new char,*b=new char;
	cin.getline(a,'\n');
	cin.getline(b,'\n');
	cout<<my_strcmp(a,b)<<endl;
}