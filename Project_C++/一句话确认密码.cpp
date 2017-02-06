#include<iostream>
int main()
{
    std::string in;
    std::cout<<((std::cin>>in,in)=="password"?"通过":"密码错误");
}