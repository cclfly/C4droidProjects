#include<stdio.h>
#include <math.h>
int yinzi(int n)
{
	for (int i=2;i<=sqrt(n);i++)
	{
		if (n%i==0)
		{
			printf("%dx",i);
			return yinzi(n/i);
		}
	}
	printf("%d",n);
	return 0;
}
main()
{
	int n;
	printf("please input a number:\n");
	scanf("%d",&n);
	yinzi(n);
}