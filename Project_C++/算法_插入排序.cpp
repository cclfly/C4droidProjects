#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#define N 10000
int main()
{
	srand(time(0));
	int *n=new int[N];
	for(int i=0;i<N;i++)
	{
		n[i]=rand()%1000;
		printf("%d  ",n[i]);
	}
	printf("\n");
	/*******************************/
	time_t start=clock();
	int key;
	for(int j=1;j<N;j++)
	{
		key=n[j];
		int i=j-1;
		while(i>=0&&n[i]>key)
		{
			n[i+1]=n[i];
			i--;
		}
		n[i+1]=key;
	}
	time_t stop=clock();
	/*******************************/
	for(int i=0;i<N;i++)
	{
		printf("%d  ",n[i]);
	}
	printf("\n");
	printf("\n\n\t%d个数插入排序，耗时%dus",N,stop-start);
	return 0;
}