#include<stdio.h>

int tenf(int n)
{
	int s=1,i;
	for (i=1;i<=n;i++)
	{
		s=10*s;
	}
	return s;
}
int dpt(int x,int n)
{
	x=x%tenf(n);
	x=x/tenf(n-1);
	return x;
}
int main(void)
{
	int x,n,i;
	int a[10];
	scanf("%d",&x);
	for (n=1;tenf(n-1)<x;n++)
	{
		a[n-1]=dpt(x,n);
	}
	for (i=1;i<n;i++)
	{
		printf("%d ",a[i-1]);
		}
}
		