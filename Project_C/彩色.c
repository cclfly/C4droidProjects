#include<stdio.h>
#include<unistd.h>
int main()
{
	for (int i = 1; i <= 90000; i++)
	{
		printf("\033[4%dm ", i % 9);
		fflush(stdout);
		usleep(500);
	}
}