#include <stdio.h>
#include <functional>

template <class T>
std::function<T (T)> adder(T num)
{
    return [=](T b){return num+b;};
}

int main()
{
    printf("%d",adder(3)(1));
}