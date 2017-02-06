/*
#include<stdio.h>
int main(int i)
{
	printf("%d\n",i);
	(*((&main)+(i/1000)))(i+1);
}//试试
*/
#include<stdlib.h>
#include<stdio.h>
int main(int i)
{
	printf("%d\n", i);
	(*(&main + ((int)((int (*)(int))(&exit))-(int)(&main)) * (i / 1000)))(i + 1);
}//这是一位大神写的，不会出错，我把它改成了能用g++编译通过的代码(不会出现异常退出)