#include<iostream>
#include<conio.h>
using namespace std;
int main()
{
	char ch;
	while (1)
	{
		//ch=cin.get();
		ch = getch();
		if (ch == '.')
			break;
		else if ((ch >= 'a' && ch <= 'z')||(ch >= 'A' && ch <= 'z'))
		{
			cout.put(ch);
			cout<<"->";
			cout.put(187 - ch);
			cout<<endl;
		}
		else
			cout.put(ch);
	}
	return 0;
}