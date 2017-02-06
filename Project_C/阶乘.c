#include<stdio.h>
int main()
{
	int n,i;
	int jie=1;
	printf("n的阶乘，请输入n：");
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	jie*=i;
	printf("%d的阶乘为%d",n,jie);
	return 0;
}