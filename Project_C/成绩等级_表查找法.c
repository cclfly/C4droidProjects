#include <stdio.h>
int main()
{
	char *cj[6]={"优秀","优秀","良好","中等","及格","不及格"};
	float a;
	scanf("%f",&a);
	printf("%s\n",cj[6-((int)a-40)/10]);
	return 0;
}