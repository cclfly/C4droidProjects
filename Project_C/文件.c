#include <stdio.h>
#include <stdlib.h>
int main()
{
	char ch;
	FILE *fp;
	if ((fp = fopen("c4.txt", "a+") ) == NULL)
	{
		printf("cannot open this file\n");
		exit(0);
	}
	ch = getchar();
	if (ch != '#')
	{
		fputc(ch, fp);
		ch = getchar();
	}
	ch=getchar();
	putchar(10);
	fclose(fp);
}