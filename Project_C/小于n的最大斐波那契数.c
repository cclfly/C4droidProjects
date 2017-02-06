#include <stdio.h>

int fun(int n)
{
	int a=0;
	int b=1;
	//int count=1;
	do{
		int tmp=b;
		b=a+b;
		a=tmp;
		//count++;
	}while (b<n);
	return a;
}

int main()
{
	printf("%d\n",fun(1000));
	return 0;
}