#include<stdio.h>
#include<math.h>
int main()
{
	long s = 0, x = 0;
	int i, j, n;
	printf("输入一个数：");
	scanf("%d", &n);
	for (i = 0; i < n; i++)
	{
		x=0;
		for (j = 0; j < i + 1; j++)
			x += (i + 1) * pow(10, j);
		printf("%ld+", x);
		s += x;
	}
	printf("\b=%ld", s);
}