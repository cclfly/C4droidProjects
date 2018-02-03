/*
有n人围成一圈，顺序排号。从第1个人开始报数（从1到3报数），凡报到3的人退出圈子，问最后留下的是原来的第几号的那位。
输入
初始人数n
输出
最后一人的初始编号
样例输入
3
样例输出
2
*/
#include <iostream>
#include <list>

using namespace std;

int main()
{
	list<int> ls;
	int N,count=1;
	
	cin>>N;
	
	for(int i=0;i<N;++i)
	    ls.push_back(i+1);
	
	for(auto it=ls.begin();ls.size()>1;it++,count++)
	{
		if(it==ls.end())
		    it=ls.begin();
		    
		if(count==3)
		{
			ls.erase(it);
			count=0;
		}
	}
	
	cout<<ls.front()<<endl;
	
	return 0;
}