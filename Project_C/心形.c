#include <stdio.h>
#include <math.h>
#include<stdlib.h>
#include<conio.h>
//#include <windows.h>
#define r 10
#define R 172
#define ai "  祝天下有情人，情人节快乐！  "
//#define ai " (@_@) I LOVE MY MOTHER (@_@) "    //输入30个字符		\3 : 补心
//	FILE *fp;
	int n;
	int i, j, e;
	int a;
void xinxing()
{
		for (i = 1, a = r; i<(r / 2); i++, a--)
	{
		for (j = (int)(r - sqrt((r*r - (a - i)*(a - i)))); j>0; j--)
		{
			printf(" ");
		//	fprintf(fp, "%s", " ");
		}
		for (e = 1; e <= 2 * sqrt((r*r - (a - i)*(a - i))); e++)
		{
			printf("*");
		//	fprintf(fp, "%s", "*");
		}
		for (j = (int)(2 * (r - sqrt((r*r - (a - i)*(a - i))))); j>0; j--)
		{
			printf(" ");
		//	fprintf(fp, "%s", " ");
		}
		for (e = 1; e <= 2 * sqrt((r*r - (a - i)*(a - i))); e++)
		{
			printf("*");
		//	fprintf(fp, "%s", "*");
		}
		printf("\n");
	//	fprintf(fp, "%s", "\n");
	}
	for (i = 1; i<40; i++)
	{
		if (i == 6)
		{
			printf("%s",ai);
			i += 30;
		}
		printf("*");
	//	fprintf(fp, "%s", "*");
	}
	printf("\n");
	for (i = 1; i <= R / 2; i++)
	{
		if (i % 2 || i % 3)continue;
		for (j = (int)(R - sqrt((double)(R*R - i*i))); j>0; j--)
		{
			printf(" ");
		//	fprintf(fp, "%s", " ");
		}
		for (e = 1; e <= 2 * (sqrt((double)(R*R - i*i)) - (R - 2 * r)); e++)
		{
			printf("*");
		//	fprintf(fp, "%s", "*");
		}
		printf("\n");
	}
}
int main(void)
{

/*	if ((fp = fopen("LOVE.txt", "w")) == NULL)
	{
		printf("File open error!\n");
		exit(0);
	}*/
	xinxing();
//	printf("请选择播放形式:\n自动播放: 按 1 , 控制播放: 按 0 \n");
//	printf("按完数字后请按Enter键\n");
/*	scanf("%d", &n);
	if (n == 0)
	{
		printf("任意键变换···");
		while (1)
		{
			system("color a");
		//	system("pause");
			getch();
			system("color b");
		//	system("pause");
			getch();
			system("color c");
		//	system("pause");
			getch();
			system("color d");
		//	system("pause");
			getch();
			system("color e");
		//	system("pause");
			getch();
			system("color f");
		//	system("pause");
			getch();
		}
	}
	else*/
	{
		printf("任意键结束···");
		while (!kbhit())
		{
			clrscr();
			printf("\033[31m\033[1m");
			xinxing();
			 sleep(1);
			 clrscr();
			printf("\033[32m\033[1m");
			xinxing();
			 sleep(1);
			 clrscr();
			printf("\033[33m\033[1m");
			xinxing();
			 sleep(1);
			 clrscr();
			printf("\033[34m\033[1m");
			xinxing( );
			sleep(1);
			clrscr();
			printf("\033[35m\033[1m");
			xinxing();
			 sleep(1);
			 clrscr();
			printf("\033[36m\033[1m");
			xinxing();
			 sleep(1);
			 clrscr();
			printf("\033[37m\033[1m");
			xinxing();
			 sleep(1);
		}
	}
}