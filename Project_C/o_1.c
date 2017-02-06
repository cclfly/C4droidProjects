#include<stdio.h>
#include<ctype.h>
int main(void)
{
	int first=0;
	char second;
	int a;
	part1:
	printf("请输入5位字母密码:\n");
 char c1,c2,c3,c4,c5,c6,c7,c8,c9,c0;
 scanf("%c%c%c%c%c",&c1,&c2,&c3,&c4,&c5);
 c6=c1+4;
 c7=c2+4;
 c8=c3+4;
 c9=c4+4;
 c0=c5+4;
 {
 if (c6==103,c7==108,c8==109,c9==114,c0==101) 
 printf("密码正确\n\n");
else
return 0;

}


part2:printf("请选择\n礼物系统请按a\n利率系统请按b\n数字比大小系统请按c\n");
	char go;
	go=getchar();
	scanf("%c",&go);
	switch(go)
	{
		case 'a':goto part3;break;
		case 'b':goto part4;break;
		case 'c':goto part5;break;
		default:printf("输入有误,请重新输入\n");
		goto part2;
	}
	return 0;
	;
	part3:
	{
	char name[100];
	int first = 0;
	char second;
	char a[] = "Please 到时不要太感动～";
	int i;
	int b;
	
cart1:printf("欢迎来到礼物系统。\n请输入您的名字：");
	scanf("%s", name);
	printf("%s\n", name);
	for (i = 0; i < 10; i++)
		printf("%c", 3);
	printf("\n");
	printf("%s\n", a);
	for (i = 0; i < 10; i++)
		printf("%c", 3);
	printf("\n");
	printf("继续请按1，重新开始请按2,结束请按q。\n\n");
	first = getchar();
	while ((first = getchar()) != 'q')
	{
		if (first == '\n')
			continue;
		if (isdigit(first))
		{
			switch (first)
			{
			case '2':
				goto cart1;
			case '1':
				printf("%s，不要着急，礼物在后面～～～.\n\n",
					   name);
				printf("继续请按1，结束请按q\n");
				while ((second = getchar()) != 'q')
				{
					if (second == '\n')
						continue;
					if (second == '1')
					{
						for (b = 0; b < 50; b++)
							printf
								("%s,我草泥马啊！！！！！         ",
								 name);
						printf("\n\n\n");
						getchar();
						goto cart2;
					}
				}
				getchar();
				goto cart2;
			default:
				printf("输入有误，请重新输入\n");
			}
			while (getchar() != '\n')
				continue;
		}
	}
	cart2:printf("谢谢！～\n请输入任意键\n");
	getchar();
	goto part6;
	}
part4:
{
	printf("欢迎来到银行利率计算系统\n(本系统的第一方案为活期存款，第二方案为一年定期存款，第三方案为两次半年期存款)\n那么请输入：\n本金,第一方案利息,第二方案利息,第三方案利息\n");
float  p1,p2,p3,p0,r1,r2,r3;
scanf("%f,%f,%f,%f",&p0,&r1,&r2,&r3);
	p1=p0*(1+r1);
	p2=p0*(1+r2);
	p3=p0*(1+r3/2)*(1+r3/2);
	printf("第一方案本息和=%f\n第二方案本息和=%f\n第三方案本息和=%f\n",p1,p2,p3);
	goto part6;
}
part5:
{
	int a,b,c,max;
	printf("请输入三个不同整数:a,b,c:\n");
	scanf("%d,%d,%d",&a,&b,&c);
	max=a;
	if(max<b)
	max=b;
	if(max<c)
	max=c;
	printf("最大的数字为 %d\n",max);
	goto part6;
}
part6:
char over;
printf("返回请按p，结束请按任意健\n");
over=getchar();
scanf("%c",&over);
if
(over=='p')
goto part2;
else
return 0;

}