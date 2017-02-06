#include <ctime>
#include <cstdio>

void sleep(double sec)
{
   fflush(stdout);
   sec*=CLOCKS_PER_SEC;
   clock_t clock_c=clock();
   while(clock()-clock_c<sec);
}

void print_timeout(char * str,double timeout=0.05)
{
   while(*str)
   {
      putchar(*(str++));
      sleep(timeout);
   }
}

int main()
{
   print_timeout("hello world!",0.08);
   
   sleep(0.4);
}