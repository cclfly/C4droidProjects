#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<conio.h>
int main(void)
{
	char an[10];
	unsigned int a, b, c;
	srand((unsigned)time(NULL));
	while (1)
	{
		for (a = 1; a <= 1000; a++)
		{
			c = rand() % 11;
			printf("%s",an);
			for (b = 0; b <= c; b++)
			{
				putchar(' ');
			}
			sprintf(an,"\033[%dm",(c%3==1||c%3==0)?1:0);
			putchar('*');
		}
		usleep(200000);
		clrscr();
	}
	// system("pause");
}