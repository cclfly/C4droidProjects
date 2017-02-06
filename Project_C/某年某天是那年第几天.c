#include <stdio.h>
int days[2][12]={
	{31,28,31,30,31,30,31,31,30,31,30,31},
	{31,29,31,30,31,30,31,31,30,31,30,31}
};
int lorc(int y)//闰年返回1，平年返回0
{
	return y%400?(y%100?(y%4?0:1):0):1;
}
int main()
{
	int y,m,d;
	scanf("%d.%d.%d",&y,&m,&d);
	if (y<0||m<0||d<0||m>12||d>days[lorc(y)][m-1])
	{
		return -printf("error\n");
	}
	printf("%d年%d月%d日是%d年的第",y,m,d,y);
	int sum=d;
	while (--m)
	{
		sum+=days[lorc(y)][m-1];
	}
	printf("%d天\n",sum);
	return 0;
}