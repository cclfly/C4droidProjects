#include<iostream>
using namespace std;
#define lilv 0.08
//利率
#define nianzhichu 10 
//年支出
int main(void)
{
	float x=100;
	int i;
	for(i=0;x>0;)
	{
		x+=x*lilv;
		x-=nianzhichu;
		i++;
		cout<<"第"<<i<<"年后余额为"<<x<<"万元"<<endl;
	}
	cout<<"第"<<i<<"年将取完钱";
	return 0;
}