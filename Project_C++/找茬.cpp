#include<iostream>
#include<stdlib.h>
#include<cmath>
using namespace std;
int main()
{
	int i, j;
	char qf[1500];
	for (i = 0; i < 1500; i++)
		qf[i] = '6';
	srand(time(0));
	i = rand() % 1500;
	qf[i] = 'b';
	j = 1;
	for (i = 0; i < 1500; i++)
	{
		switch (i % 50)
		{
		case 0:
			cout << j++ << '\t';
		default:
			cout << qf[i];
			break;
		}
		if(i%50==49)
		cout<<'\n';
	}
}