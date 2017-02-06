#include <iostream>
using namespace std;
template < typename T > void fun (int x, T t)
{
}

template <> void fun < int >(int x, int a)
{
    cout << a;
}

int main ()
{
    fun (6, 9);
}