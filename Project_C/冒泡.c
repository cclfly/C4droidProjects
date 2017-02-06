#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
void maopao(int *a, int n);
int main()
{
	int *a, b, n, i;
	char *ch;
	ch = (char *)malloc(sizeof("将生成"));
	do
	{
		printf("\t1.手动输入\n");
		printf("\t2.随记生成\n");
		printf("请选择：");
		scanf("%d", &b);
		if (b == 1 || b == 2)
			break;
		printf("错误！");
		sleep(3);
		clrscr();
	}
	while (1);
	strcpy(ch, (b == 1) ? "想输入" : "将生成");
	printf("%s    个数\b\b\b\b\b\b\b", ch);
	scanf("%d", &n);
	a = (int *)malloc(sizeof(int) * n);
	for (i = 0; i < n; i++)
	{
		if (b == 1)
		{
			scanf("%d", &a[i]);
		}
		else
		{
			a[i] = rand() % 100 * ((rand() % 2) ? 1 : -1);
		}
	}
	printf("\n数列为：\n");
	for (i = 0; i < n; i++)
	{
		if (a[i] > 0)
			printf(" ");
		printf("%d\t", a[i]);
		if (i % 8 == 7)
			printf("\n");
	}
	printf("\n\n排序后：\n");
	maopao(a, n);
	for (i = 0; i < n; i++)
	{
		if (a[i] > 0)
			printf(" ");
		printf("%d\t", a[i]);
		if (i % 8 == 7)
			printf("\n");
	}
	return 0;
}

void maopao(int *a, int n)
{
	int i, j, k, c;
	for (j = 0; j < n; j++)
	{
		for (i = 0; i < n; i++)
		{
			if (*(a + i) > *(a + i + 1))
			{
				c = *(a + i);
				*(a + i) = *(a + i + 1);
				*(a + i + 1) = c;
			}
			else;
		}
	}
}