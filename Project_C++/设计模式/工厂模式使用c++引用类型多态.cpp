/*
 * c++的引用多态以及模板方法在设计模式（工厂模式）的应用
 */
#include <iostream>

using namespace std;

class Product{
    public:
    virtual void function() = 0;
};
class Product1 :public Product{
    public:
    void function()
    {
        cout << "1" << endl;
    }
};
class Product2 :public Product{
    public:
    void function()
    {
        cout << "2" << endl;
    }
};

class Factory{
    public:
    template<typename T>
    static Product &create()
    {
        return *(new T);
    }
};

int main()
{
    Factory::create<Product1>().function();
    Product &pro = Factory::create<Product2>();
    pro.function();
    return 0;
}