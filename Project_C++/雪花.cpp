#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<conio.h>
using namespace std;
#define Z "＊"
#define Y '*'
#define X '.'
void xuehua(int n);
int main(void)
{
	/* for(int j=9;j;j--) for (int i=0;i<=9;i++) cout<<i; */// 一排60个字符
	srand(time(0));
//	for(;1;)
	xuehua(0);
	return 0;
}

void da(int s)
{
	int i=0, j=0,k=0;
	for (; s >= 0; s-=2)
	{
		 for (i = 0; i < 60; i++)
		{
			if (i == s)
			{
				cout << Z<<flush;
				usleep(500000);
				cout << "\b\b  ";
			}
			else
				cout << " ";
		}
		cout << '\n';
		if(k++>20)break;
	}
	cout<<'\v';
}


void xuehua(int n)
{
	int r;
	r=rand()%60;
	if(n==0)
	{
		da(r);
	}
	else;
}