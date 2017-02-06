#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#ifndef __WIN32
#define T 1000.
#else
#define T 1.
#endif

struct
{
	uint64_t *list;
	uint32_t size;
} prime_number_list;

int init_list(int len)
{
	if (len < 1)
		return -1;
	prime_number_list.list = (uint64_t *) malloc(sizeof(uint64_t) * len);
	*prime_number_list.list = 2;
	prime_number_list.size = 1;
}

int main()
{
	uint8_t was_prime_number = 1;
	uint32_t d = 0;
	uint64_t i = 0, j = 0;
	uint64_t a = 0, b = 0;
	uint64_t x = 0;
	// printf("2-x的素数 x=");
	scanf("%llu", &a);
	scanf("%llu", &b);
	x = b;
	int s = clock();
	init_list(1.2 * x / log(x));
	for (i = 3; i <= x; i++)
	{
		d = sqrt(i);
		for (j = 0; j < prime_number_list.size; j++)
		{
			if (prime_number_list.list[j] > d)
				break;
			if (i % prime_number_list.list[j] == 0)
			{
				was_prime_number = 0;
				break;
			}
		}
		if (was_prime_number)
			prime_number_list.list[prime_number_list.size++] = i;
		was_prime_number = 1;
	}
	
	for (int i = 0; i < prime_number_list.size; ++i)
		 if (prime_number_list.list[i] > a)
		{
			printf("%llu", prime_number_list.list[i]);
			if (i < prime_number_list.size - 1)
				putchar(' ');
		}
//	printf("\n素数总数:%u 所用时间:%llfms", prime_number_list.size, (clock() - s) / T);
	free(prime_number_list.list);
}