#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
int main(void)
{
	sleep(3600);
	system("su -c reboot");
	return 0;
}