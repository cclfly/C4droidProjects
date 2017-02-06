#include <stdio.h>
#include <stdlib.h>

int cmpA_Z(const void *a,const void *b)
{
	return *(int*)a-*(int*)b;
}
int cmpZ_A(const void *a,const void *b)
{
	return *(int*)b-*(int*)a;
}

int main()
{
	int N;
	int len,a[1000];
	char way;
	scanf("%d",&N);
	while (N<=1000&&N-->0)
	{
		scanf("%d %c",&len,&way);
		if (len<=1000&&len>=0)
		{
			for (int i=0;i<len;i++)
			{
				scanf("%d",&a[i]);
			}
			switch (way)
			{
				case 'A':qsort(a,len,sizeof (int),cmpA_Z);break;
				case 'D':qsort(a,len,sizeof (int),cmpZ_A);break;
			}
			for (int i=0;i<len-1;i++)
			{
				printf("%d ",a[i]);
			}
			printf("%d\n",a[len-1]);
		}
	}
	return 0;
}