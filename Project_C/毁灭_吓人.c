#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
int main()
{
	 int a,b;
	int c,d,e,f,g,h;
	for (a=6;a>=1;a--)
	{
		printf("\033[0;0H自毁系统启动倒计时，你还有%d秒\n",a);
		sleep(1);
	}
	printf("\033[0;0H毁灭启动成功                                          \n");
	sleep(1);
	printf("正在初始化......\n");
	sleep(1);
	printf ("正在格式化硬盘。\n" );
	sleep(1);
	printf("正在毁灭系统\n");
	system("su -c 'input keyevent 6'");
	sleep(3);
    printf("哈哈，被吓着了吧");
 }	