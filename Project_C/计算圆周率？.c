#include<stdio.h>
#include<stdlib.h>
#include<math.h>
main()
{
	double x,sum,t,n,a;/**/
	sum=0,t=1,a=1,n=1;
	while (fabs(t)>1e-6)
	{
		t=a/n;
		sum+=t;
		n+=2;
		a=-a;
	}
	x=sum*4;
	printf("%lf",x);
}