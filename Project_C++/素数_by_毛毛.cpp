// 注意 本代码使用c++11多线程库
// 建议使用vs2012以上或gcc4.91以上编译
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<thread>
#include<mutex>
#ifndef _WIN32
#include<conio.h>
#define T 1000.
#define FILENAME "/sdcard/素数.myq"
#else
#include<windows.h>
#define FILENAME "%USERPROFILE%\\Desktop\\素数.myq"
#define T 1.
#define sleep(n) Sleep(n*1000)
#endif
//#define NO_SHOWN_OUTPUT
struct
{
	uint32_t size;
	uint64_t *list;
} prime_number_list;

int init_list(int len)
{
	if (len < 1)return -1;
	prime_number_list.list = (uint64_t*) malloc(sizeof(uint64_t)*len);
	*prime_number_list.list = 2;
	prime_number_list.size = 1;
}
std::mutex mutex;
#ifndef NO_SHOWN_OUTPUT
std::mutex output_mutex;
#endif
std::mutex mutex2;
uint64_t x = 0;
uint64_t current_number=3;
uint8_t stop_flag=0;
void calc()
{
	uint8_t was_prime_number = 1;
	uint32_t d=0;
	uint64_t i=0;
	while(current_number<=x)
	{
		mutex2.lock();
		i=current_number;
		current_number+=2;
		mutex2.unlock();
		d = sqrt(i);
		for (size_t j = 0; j < prime_number_list.size; j++)
		{
			if (prime_number_list.list[j] > d)break;
			if (i % prime_number_list.list[j] == 0)
			{
				was_prime_number = 0;
				break;
			}
		}
		if (was_prime_number)
		{
			mutex.lock();
			prime_number_list.list[prime_number_list.size++] = i;
			mutex.unlock();
//		output_mutex.lock();
#ifndef NO_SHOWN_OUTPUT
printf("%lld ",i);
#endif
//			output_mutex.unlock();
		}
		was_prime_number = 1;
	}
}
#ifdef NO_SHOWN_OUTPUT
void output()
{
	while(1)
	{
		printf("进度:%.2llf%%",(current_number/(double)x)*100);
		fflush(stdout);
		if(current_number>x)break;
		sleep(1);
		printf("\b\b\b\b\b\b\b\b\b\b\b\b");
	}
}
#endif
int main()
{
	printf("2-x的素数   x=");
	scanf("%llu", &x);getchar();
	int s = clock();
	init_list(1.2 * x / log(x));
	std::thread t1(calc);
	std::thread t2(calc);
	std::thread t3(calc);
	std::thread t4(calc);
#ifdef NO_SHOWN_OUTPUT
	std::thread output_t(output);
#endif
	t1.join();t2.join();t3.join();t4.join();
	int e=clock();
#ifdef NO_SHOWN_OUTPUT
	output_t.join();
#endif
	printf("\n素数总数:%u 所用时间:%llfms\n\n是否储存到文件？Y/N\n", prime_number_list.size,(e- s) / T);
	char c=getchar();getchar();
	char *filename=FILENAME;
	if(c=='Y'||c=='y')
	{
		FILE *out=fopen(filename,"wb");
		if(out==NULL){printf("打开%s文件失败",filename);return -1;}
		printf("是否储存为二进制文件？(Y/N)   否则储存为文本文件\n->");
		c=getchar();
		if(c=='y'||c=='Y')
		{
			fwrite(&prime_number_list.size,sizeof(uint32_t),1,out);
			fwrite(prime_number_list.list,sizeof(uint64_t),prime_number_list.size,out);
		}
		else
		for(size_t i=0;i<prime_number_list.size;i++)
		{
		fprintf(out,"%llu  ",prime_number_list.list[i]);
		if((i+1)%10==0)
		fprintf(out,"\n");
		}
		printf("已导出到%s",filename);
		fclose(out);
	}else
	{
		printf("Done");
	}
	free(prime_number_list.list);
}