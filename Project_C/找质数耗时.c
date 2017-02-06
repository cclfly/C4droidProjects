#include<stdio.h>
#include<time.h>
//#define DEBUG  //取消这行的注释能输出质数


int main()
{
	unsigned int start = 1;
	unsigned int end = 10000;
	int s, e;
	unsigned int d = 0;

#ifdef DEBUG
	bool flag = false;
#endif
	s = (clock() / 1000);
	for (unsigned int i = start; i <= end; i++)
	{
#ifdef DEBUG
		flag = false;
#endif
		d = i / 2;
		for (unsigned int k = 2; k <= d; k++)
		{
			if ((i % k) == 0)
			{
#ifdef DEBUG
				flag = true;
#endif
				break;
			}
		}
#ifdef DEBUG
		if (!flag)
			printf("%lu\n", i);
#endif
	}
	e = (clock() / 1000);
	printf("ok,寻找%d到%d的质数 花费%d毫秒", start, end, e - s);
}