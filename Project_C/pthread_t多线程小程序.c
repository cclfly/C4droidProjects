#include<stdio.h>
#include<pthread.h>
#include<conio.h>
bool quit=false;
void *t(void *)
{
	while (getch()!='q');
	quit=true;
}

int main()
{
	pthread_t th;
	int i=0;
	pthread_create(&th,NULL,t,NULL);
	while (!quit)
	{
		clrscr();
		printf("%d\n",i++);
		usleep(100000);
	}
	pthread_join(th,NULL);
	return 0;
}//多线程小程序