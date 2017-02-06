#include<stdio.h>
#include<stdlib.h>
int main()
{
	int **a;
	int i, j, n;
	printf("打印杨辉三角行数：");
	scanf("%d", &n);
	printf("\033[?25l");
	a = (int **)malloc(sizeof(int *) * n);
	for (i = 0; i < n; i++)
	{
		a[i] = (int *)malloc(sizeof(int) * (i + 1));
		a[i][0] = 1;
		a[i][i] = 1;
		for (j = 0; j < n - i; j++)
			printf(" ");
		for (j = 0; j < i + 1; j++)
		{
			if (a[i][j] != 1)
				a[i][j] = a[i - 1][j - 1] + a[i - 1][j];
			printf("%d,", a[i][j]);
		}
		printf("\b \n");
	}
	for (i = 0; i < n; i++)
	{
		free(a[i]);
		a[i] = NULL;
	}
	free(a);
	return 0;
}