#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
int main(void)
{
	char ch;
	printf("要淡定。。。\n");
	sleep(1);
	for (ch = 'a'; ch <= 'z'; ch++)
	{
		sleep(1);
		printf("%c\n", ch);
//		system("su -u input keyevent 6");
	}
}