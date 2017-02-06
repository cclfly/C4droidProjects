//这是个秒表
//p键记录秒数
//c键清空记录
//q键退出程序

#include <stdio.h>
#include<conio.h>
#include<unistd.h>
#include<pthread.h>

short flag = 0;

struct time
{
	int m;
	int s;
	int ms;
};

void *func(void *data)
{
	struct time *t = (struct time *)data;
	int record = 0;
	char in;
	while (!flag)
	{
		in = getch();
		if (in == '\n')
			continue;
		 if (in == 'p')
		{
			record++;
			gotoxy(1, record + 2);
			printf("记录%d->%.2d:%.2d:%.3d", record, t->m, t->s, t->ms);
		}
		if (in == 'c')
			clrscr(), record = 0;
		if (in == 'q')
			flag = 1;
	}
	return 0;
}

int main()
{
	struct time t = { 0, 0, 0 };

	pthread_t in;
	pthread_create(&in, NULL, &func, &t);

	for (t.ms; !flag; t.ms++)
	{
		printf("%.2d:%.2d:%.3d", t.m, t.s, t.ms);
		fflush(stdout);
		if (t.ms > 1000)
			t.s++, t.ms = 0;
		if (t.s > 60)
			t.m++, t.s = 0;
		usleep(1000);
		if (t.ms < 10000)
			gotoxy(1, 1);
	}
	pthread_join(in, NULL);
	return 0;
}