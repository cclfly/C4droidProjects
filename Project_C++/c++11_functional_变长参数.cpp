#include <iostream>
#include <functional>
using namespace std;

template <typename T>
struct identity
{
  typedef T type;
};

template <typename... T>
void func(typename identity<std::function<void(T...)>>::type f, T... values) {
  f(values...);
}

int main() {
  //func([](int x, int y, int z) { std::cout << (x*y*z) << std::endl; }, 3, 6, 8);
  func([](int a, int b, int c, int d){
  	cout<<a+b+c+d<<endl;
  }, 1, 2, 3, 4);
  return 0;
}