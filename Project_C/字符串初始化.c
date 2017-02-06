#include<stdio.h>
#include<string.h>
int main()
{
	char a[100],b[100];
	memset(a,0,100);
	memset(b,'\0',100);
	printf("%d %d\n",sizeof(a),strlen(a));
	printf("%d %d\n",sizeof(b),strlen(b));
	return 0;
}