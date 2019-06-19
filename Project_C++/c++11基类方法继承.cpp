#include <iostream>
using namespace std;
struct A
{
    A(int i){cout<<i<<endl;}
};
struct B:public A
{
    using A::A;
};
int main()
{
    B(233333);
    return 0;
}