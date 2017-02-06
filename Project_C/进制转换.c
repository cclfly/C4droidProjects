#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

void fenli(int b, int c, int n, int *a);
int weishu(int b, int n);

int main(void)
{
	int *a;						// 存储位权
	int b;						// n进制的数
	int c;						// 位数
	int n;						// 进制
	while (1)
	{
		printf("请选择输入进制：");
		scanf("%d", &n);
		if (!(n > 1))
		{
			clrscr();
			printf("错误！请重新输入！！！\n");
			usleep(500000);
			clrscr();
		}
		else
			break;
	}
	printf("请输入%d进制的一个数：", n);
	while (1)
	{
		scanf("%d", &b);
		c = weishu(b, n);
		if (c == 0)
		{
			printf("错误！\n");
			printf("请重新输入%d进制的数：", n);
		}
		else
			break;
	}
	printf("%d",c);
	a=(int*)malloc(sizeof(int)*c);
	fenli(b,c,n,a);
}

 int weishu(int b, int n)
{
	int i;
	for (i = 0; b > 0; i++)
	{
		if (b % 10 >= n)
		{
			i = 0;
			break;
		}
		b /= 10;
	}
	return i;
}

void fenli(int b,int c,int n,int*a)
{
	int im
	for(i=0;i<c;i++)
	{
		
	}
}