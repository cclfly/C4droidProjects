#include<stdio.h>
int myAtoi(char *str)
{
	int u=0;
	if(*str=='-')
	u=1;
	int temp=0;
	if(*str=='-'||*str=='+')
		str++;
	while(*str!='\0')
	{
		if(*str<'0'||*str>'9')
		{
			printf("错误\n");
			break;
		}
		else
			temp=temp*10+(*str-'0');
	str++;
	}
	if(u) 
	temp=-temp;
	return temp;
}
int main() 
{ 
	int myAtoi(char*str);
	int n=0; 
	char a[10];
	scanf("%s",a);
//	gets(a);
	n=myAtoi(a);
	printf("%d\n",n);
}