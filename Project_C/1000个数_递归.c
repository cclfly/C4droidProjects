#include<stdio.h>
void abc(int i, int n);
void abc(int i, int n)
{
	if (i <= n)
	{
		printf("%d ", i);
		abc(++i, n);
	}
	else;
}

int main()
{
	abc(1, 1000);
}