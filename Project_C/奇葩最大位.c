#include<stdio.h>
int main()
{
	int x,n,max;
	do{scanf("%d",&x),n=x,max=1;}
	while(n<=0);
	while((n=x)>0)
	{x=x/10;
	n=n%10;
	if(!(max<n?max=n:max))max=x;}
	printf("%d",max);
}