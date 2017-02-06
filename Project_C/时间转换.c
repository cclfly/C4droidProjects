#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

void jiesuan(int a, int b, int c, int d);

void tui(int n)
{
	int i = 0;
	for (i = 0; i < n; i++)
	{
		printf("\b");
	}
	// printf("\n");
}

int main(void)
{
	int a, b, c, d;
	printf("请输入：    天    小时    分    秒");
	tui(25);
	scanf("%d", &a);
	clrscr();
	printf("请输入：%d天    小时    分    秒", a);
	tui(19);
	scanf("%d", &b);
	clrscr();
	printf("请输入：%d天%d小时    分    秒", a, b);
	tui(11);
	scanf("%d", &c);
	clrscr();
	printf("请输入：%d天%d小时%d分    秒", a, b, c);
	tui(5);
	scanf("%d", &d);
	clrscr();
	printf("请输入：%d天%d小时%d分%d秒", a, b, c, d);
	printf("\n");
	jiesuan(a,b,c,d);
}

void jiesuan(int a, int b, int c, int d)
{
	int secoud = 0, minute = 0;
	int hour = 0, day = 0;
	int week=0;
	b += a * 24;
	c += b * 60;
	d += c * 60;
	printf("合计%d秒\n", d);
	if (d >= 60)
	{
		secoud = d % 60;
		minute = d / 60;
					printf("合计%f分\n",(float)d/60);
		if (minute >= 60)
		{
			hour=minute/60;
							printf("合计%f小时\n",(float)d/60/60);
			if(hour>=24)
			{
				day=hour/24;
				printf("合计%f天\n",(float)d/60/60/24);
				if(day>=7)
				{
					week=day/7;
				}
			}
		}
	}
}