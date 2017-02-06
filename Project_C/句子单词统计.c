#include<stdio.h>
int main()
{
	char string[81][81];
	char c;
	int i, num = 0, word = 0, j;
	c=1;
	for (i = 0; i < 81; i++)
	{
		for (j = 0; j < 81; j++)
		{
			string[i][j] = getchar();
			if (string[i][j] == '.')
			{
				string[i][j] = '\0';
				break;
			}
			if (string[i][j] == '\n')
			{
				c = 0;
				break;
			}
		}
		if (c == 0)
			break;
	}
	int x;
	for (x = 0; x < i; x++)
	{
		word=0;
		num=0;
		for (j = 0; (c = string[x][j]) != '\0'; j++)
			if (c == ' ')
				word = 0;
			else if (word == 0)
			{
				word = 1;
				num++;
			}
	printf("There are % d words in %d line. \n", num,x+1);
	}
	return 0;
}