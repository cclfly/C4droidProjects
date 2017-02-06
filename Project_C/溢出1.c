#include<stdio.h>
int main()
{
	signed char a = 127;
	printf("%d  %#x\n", a, a);
	char i = 128;
	while (i--)
	{
		a += 1;
		printf("%d  %#x\n", a, a);
	}
}