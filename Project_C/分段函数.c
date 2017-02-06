/*
                  分段函数

              1                       (n=1)
 k(n)=  (k(n-1)/5)-3     (n为偶数)
             k(n-1)^2*3       (n为奇数)
 */
#include <stdio.h>
#include <math.h>
double k(int n)
{
	if(n==1)
	return 1;
	if(n%2==0)
	return (k(n-1)/5)-3;
	if(n%2==1)
	return pow(k(n-1),2)*3;
}
int main()
{
	printf("%lf",k(7));
	return 0;
}