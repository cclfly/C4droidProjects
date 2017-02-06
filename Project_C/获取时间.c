#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int main()
{
        time_t p;
        char s[30];
        time(&p);
        strcpy(s,ctime(&p));
        printf("%s\n",s);
        return 0;
}