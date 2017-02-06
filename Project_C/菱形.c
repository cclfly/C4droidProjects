#include<stdio.h>
main()
{
	int a, b, c, n, s = 0, e = 0, x = 0, y = 0;
	printf("请输入一个数");
	scanf("%d", &n);
	for (a = 1; a <= n; a++)
	{
		for (b = n - 1; b >= a; b--)
		{
			printf(" ");
		}
		for (c = 1; c <= 2 * a - 1; c++)
		{
			printf("*");
			e++;
		}
		printf("\n");
		x++;
	}
	for (a = 1; a <= n - 1; a++)
	{
		for (b = 1; b <= a; b++)
		{
			printf(" ");
		}
		for (c = 2 * n - 3; c >= 2 * a - 1; c--)
		{
			printf("*");
			s++;
		}
		printf("\n");
		y++;
	}
	printf("*个数：%d\n 行数：%d", e + s, x + y);
}