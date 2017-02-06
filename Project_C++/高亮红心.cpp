#include<iostream>
int main()
{
	char ch[]="\t\t\3\n\t\3\t\3\t\3\n\3\t\3\t\3\t\3\t\3\n";
	for(int i=0;i<22;i++)
	{
		if(ch[i]=='\3')
		std::cout<<"\033[;31m♥ \033[1m";
		else
		std::cout<<ch[i];
	}
//	std::cout << ch;
	return 0;
}