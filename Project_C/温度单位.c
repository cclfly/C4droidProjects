#include<stdio.h> 
int main()
{
	float c,f;
	printf("\n 请输入华氏温度\(以回车结束\)\n ");
	printf("     ℉\b\b\b\b\b");
	scanf("%f",&f); 
	c=(f-32)*5/9;
	printf(" 转换成摄氏温度是：%.2f℃\n",c);/*浮点型用f*/
    return 0;
} 