#include<iostream>
#include<stdlib.h>
#include<conio.h>
using namespace std;
int main(void)
{
	int i;
	char ch[] = "移民多关心咯合同工洗呢紫色为了她你周一";
	// cout<<ch<<endl;
	for (i = 0; ch[i] != 0; i++)
	{
		cout << ch[i]<<flush;
		usleep(100000);
/*		if(i%3==2)
		{
			//cout<<endl;
			//cout<<'\033[3D';
			cout<<flush;
			usleep(100000);
		}*/
	}
	cin.get();//getch();
	 return 0;
}