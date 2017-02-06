/*
 *  约瑟夫环问题
 *  gcc
 */
#include<stdio.h>
#include<malloc.h>
typedef enum{ false, true } bool;
bool flag(int *a, int n)
{
	int i, c = 0;
	for (i = 0; i < n; i++)
	{
		if (a[i] != 0)
			c++;
	}
	if (c == 1)
		return false;
	else
		return true;
}
int main()
{
	int n, s, m, *a;
	int i, j;
	scanf("%d%d%d", &n, &s, &m);
	a = (int*)malloc(sizeof(int)*n);
	for (i = 0; i < n; i++)
	{
		a[i] = i + 1;
	}
	i = s - 1;
	while (flag(a, n))
	{
		//i += (m - 1);
		for (j = 0; j < m - 1; j++)
		{
			i++;
			while (i > n - 1)
			{
				i -= n;
			}
			while (a[i] == 0)
			{
				i++;
				while (i > n - 1)
				{
					i -= n;
				}
			}
		}
		//i--;
		a[i] = 0;
		i++;
		while (a[i] == 0)
		{
			i++;
			while (i > n - 1)
			{
				i -= n;
			}
		}
	}
	for (i = 0; i < n; i++)
	{
		if (a[i] != 0)
			printf("%d\n", a[i]);
	}
	free(a);
	a = NULL;
	return 0;
}