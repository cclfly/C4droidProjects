/* 由4个不同的数字，组成的一个乘法算式，
它们的乘积仍然由这4个数字组成。
    比如： 
210 x 6 = 1260 
8 x 473 = 3784
27 x 81 = 2187 
    都符合要求。
    如果满足乘法交换律的算式算作同一种情
    况，那么，包含上边已列出的3种情况，
    一共有多少种满足要求的算式。
    */
#include<iostream>
#include<stdio.h>
int sum,sum1=0,sum2=0,sum3=0,t[10000][4];
int test (int e,int u,int o,int s)
{int k=1,i;
sum=sum1+sum2+sum3;
for (i=0;i<sum;i++)
	{
		if (t[i][0]==e&&t[i][1]==u&&t[i][2]==o&&t[i][3]==s)k=0;}
 t[sum][0]=e;t[sum][1]=u;t[sum][2]=o;t[sum][3]=s;
	return k;
}
int main()
{
	int a[5], i, j, k, f, n, p, q, r,w,v,y,x,e,u,o,s;
	for (i = 0; i < 10; i++)
	for (j = 0; j < 10; j++)
	for (k = 0; k < 10; k++)
	for (f = 0; f < 10; f++)
	if (i != j&& i != k && i != f && j != k&& j != f && k != f)
	{
	a[1] = i;
	a[2] = j;
	a[3] = k;
	a[4] = f;
	for (n = 1; n <= 4; n++)
	for (p = 1; p <= 4; p++)
	for (q = 1; q <= 4; q++)
	for (r = 1; r <= 4; r++)
	if (n != p && n != q && n != r&& p != q && p != r && q != r)
	{
	for (w=1;w<=4;w++)
	for (v=1;v<=4;v++)
	for (y=1;y<=4;y++)
	for (x=1;x<=4;x++)
	if (w != v && w != y && w != x&& v != y && v != x && y != x)
	{
	if (((e=(a[n] * 100 + a[p] * 10 +a[q])) *( u=(a[r]))) ==(o=(a[w]*1000+a[v]*100+a[y]*10+a[x]) )&&a[w]!=0){if (test(e,u,o,0)==1){sum1++;printf("%d%d%d*%d=%d%d%d%d  \n",a[n],a[p],a[q],a[r],a[w],a[v],a[y],a[x]);}}
	if (((e=(a[n] * 10 + a[p]))*(u=(a[q]*10+ a[r]))) ==(o=(a[w]*1000+a[v]*100+a[y]*10+a[x] ))&&a[w]!=0){if (test(e,u,o,0)==1){printf("%d%d*%d%d=%d%d%d%d\n",a[n],a[p],a[q],a[r],a[w],a[v],a[y],a[x]);sum2++;}}
	if (((e=a[n])*(u= a[p]) *(o=a[q]) *(s= a[r])) ==(a[w]*1000+a[v]*100+a[y]*10+a[x] )&&a[w]!=0)if (test(e,u,o,s)==1){printf("%d*%d*%d*%d=%d%d%d%d\n",a[n],a[p],a[q],a[r],a[w],a[v],a[y],a[x]);sum3++;}
	}
	}
	}
	 std::cout<<"总数："<< sum1+sum2+sum3;
}