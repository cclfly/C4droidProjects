#include<stdio.h>
#include <sys/types.h>
int main(int argc, char *argv[])
{
    char tmp[50];
    if (getuid())
    {
        puts("不是root用户");
        sprintf(tmp, "su -c %s", argv[0]);
        system(tmp);
    }
    else
    {

        puts("是root用户了");

        puts("真的是root用户啦");
    }
}