/* 刚刚看到了个题
--题目--
从1打印到1000(要求:不允许使用循环语句，判断语句，goto，条件表达式) 
*/
#include <stdio.h>
#define Out(i) printf("%d\n",i++);
#define REP(N) N N N N N N N N N N
#define Out10000(i) REP(REP(REP(REP(Out(i)))));

int main()
{
    int i = 1;
    Out10000(i);
}
 /*这不是我写的*/
