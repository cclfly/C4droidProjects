#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
template<class T>
T max(vector<T> vec)
{
	return *max_element(vec.begin(),vec.end());
}
int main()
{
	//cout<<max<int>({8,4,3,8,2,8,5,9,3,5})<<endl;
	int a,b,c;
	cin>>a>>b>>c;
	cout<<max<int>({a,b,c})<<endl;
	return 0;
}