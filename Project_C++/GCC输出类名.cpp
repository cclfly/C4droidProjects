#include <cxxabi.h>
#include <iostream>
using namespace std;
class A{};
int main()
{
    A a;
    cout<<typeid(a).name()<<endl;
    cout<<abi::__cxa_demangle(typeid(a).name(),nullptr,nullptr,nullptr)<<endl;
    return 0;
}