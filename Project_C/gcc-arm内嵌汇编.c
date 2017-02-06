#include<stdio.h>

int main()
{
	int a=10, b=4,c;
    asm (
            "add %1,%2,%0"
             :"=r"(c)       
             :"r"(a),"r"(b)
             : 
             );
      printf("%d",c);
}