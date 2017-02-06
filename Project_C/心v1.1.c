#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<conio.h>

#define ca "\033[;31;5m\033[?25l"
#define cb "\033[;32;5m\033[?25l"
#define cc "\033[;33;5m\033[?25l"
#define cd "\033[;34;5m\033[?25l"
#define ce "\033[;35;5m\033[?25l"
#define cf "\033[;36;5m\033[?25l"
#define cg "\033[;37;5m\033[?25l"

char *sc(int a);

void k(int n)
{
	int i;
	if (n >= 0)
		for (i = 0; i < n; i++)
			printf(" ");
}

void x(int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("**");
	}
}

void hc()
{
	printf("\n");
}

int main()
{
	srand(time(0));
	int i, j, l, a;
	while (!kbhit())
	{
		a = rand();
//		printf("%s                    情 人 节 快 乐 ！ ！ ！ \n",sc(rand()));
		printf("%s",sc(a));
		for (i = 8, j = 7, l = 14; i > 0; i--, j++, l -= 2)
		{
			k(i);
			x(j);
			k(l);
			x(j);
			hc();
		}
		j = 2 * j - 1;
		for (i = 0; j >= 0; i += 2, j -= 2)
		{
			k(i);
			x(j);
			hc();
		}
		gotoxy(23,7);
		printf("*********");
		gotoxy(18,8);
		printf("%s 情 人 节 快 乐 ！ ！ ！ \n",sc(rand()));
		usleep(500000);
		clrscr();
	}
}

char *sc(int a)
{
	switch (a % 7 + 1)
	{
	case 1:
		return ca;
		break;
	case 2:
		return cb;
		break;
	case 3:
		return cc;
		break;
	case 4:
		return cd;
		break;
	case 5:
		return ce;
		break;
	case 6:
		return cf;
		break;
	case 7:
		return cg;
		break;
	}
}