#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int delay=50;

void sdelay(int _delay)
{
	delay=_delay;
}

int tprintf(const char *format,...)
{
	char buffer[4096];
	va_list ap;
	va_start(ap, format);
	vsprintf(buffer, format, ap);
	va_end(ap);
	int length=strlen(buffer);
	int result=0;
	for(int i=0;i<length;buffer[i]>0x80?i+=3:i++)
	{
		buffer[i]>0x80?result+=printf("%c%c%c",buffer[i],buffer[i+1],buffer[i+2]):putchar(buffer[i]),result++;
		fflush(stdout);
		usleep(delay*1000);
	}
	return result;
}

int main()
{
	tprintf("Why are you so diao?\n");
	char *str="因为我就是那么叼！";
	sdelay(100);
	tprintf("%s",str);
}//逐字打印效果函数