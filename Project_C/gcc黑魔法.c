//gcc的部分黑魔法
#include <conio.h>
#include <ctype.h>
#define HW1 "Hello, world!\n"
#define HW2 "Hello, world!\nHello, world!\n"
#define PRINTIT(args...)    printf(args) //一个萌萌哒的变参宏取代变参函数
inline long getnum(int argc, char *argv[]) __attribute__ ((always_inline)); //赌5毛，在win平台c语言里绝逼没内联inline
int main(int argc, char *argv[])
{
	__label__ retok, retfailed; //见过酱紫的宏吗(局部跳转标签)
	int num = getnum(argc, argv);
	char buf[strlen(HW1) * num + 1];
	__typeof__(&buf[0]) //内核宏返回参数类型
	formstr(char *buf, int n) //哪个老师教过你c函数可以嵌套定义
	{
		buf[0] = '\0';
		char *hw;
		switch (n & 1)
		{
		case 1 ... 1: //case也可以有取值范围用 ... 隔开
			hw = HW1;
			break;
		case 0 ... 0://没见过吧
			n >>= 1;
			hw = HW2;
			break;
		}
		while (n-- > 0)
			strcat(buf, hw);
		return buf;
	}
	void *addr = &&retok;
	char *cp = formstr(buf, num) ? : ({ addr = &&retfailed;
									  "Failed\n";//这个三目判断式貌似少了一个
									  });
	PRINTIT(cp);
	goto *addr; //见过酱紫的goto吗
  retfailed://goto到这里
	return -1;
  retok:
	return 0;
}

long getnum(int argc, char *argv[])
{
	return (
			   {
			   long ret = 1; if (argc > 1)
			   {
			   ret = strtol(argv[1], (char **)NULL, 10);
			   if (ret < 0 || ret == LONG_MAX || ret == LONG_MIN) ret = 0;}
			   ret;} //括弧的另类用法，可以超越花括号从而定义高度集中的一个语句块作为一个表达式整体
	);
}

//#include_next等等gcc大约对标准c做了50条扩展
