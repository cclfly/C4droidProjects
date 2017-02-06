#include <iostream>
#include <vector>
#include <functional>
using namespace std;
template<class T>
class myVector:public vector<T>{
	public:
	myVector each(function<void(T)> fun){
		/*for (auto& tmp:*this)
		{
			fun(tmp);
			//cout<<tmp;
		}*/
		for(int i=0;i<this->size();++i)
		{
			fun(this->at(i));
		}
		return *this;
	}
};
int main()
{
	myVector<int> v;
	v.push_back(9);
	v.push_back(7);
	//cout<<v[0];
	v.each([](int a){cout<<a<<endl;});
}