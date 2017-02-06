#include<stdio.h>
#include<conio.h>
int main()
{
	int s;
	while ((s = getch()) != '\n')
	{
		putchar(s);
		putchar('\t');
		switch (s - '2')
		{
		case 0:
		case 1:
			putchar(s + 4);
		case 2:
			putchar(s + 4);
			break;
		case 3:
			putchar(s + 3);
		default:
			putchar(s + 2);
			break;
		}
		printf("\n");
	}
	return 0;
}