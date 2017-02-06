/*
 *  开-O2优化尾递归
 */

#include <stdio.h>

int i=0;

int main()
{
    if(++i%100==0)
    printf("%d\n",i);
    return main();
}