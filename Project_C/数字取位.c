#include<stdio.h>
int wei(long);
int main()
{
	long a;
	scanf("%ld",&a);
	printf("输入的是%d位数",wei(a));
	return 0;
}
int wei(long a)
{
	int i=0;
	do
	{
		int b;
		printf("%d\n",a%10);
		i++;
	}while(a/=10);
	return i;
}