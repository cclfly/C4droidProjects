#include<cstdio>

class test
{
    public:
    test():k(9.9),i(9),o(9.f){};
    private:
    double k;
    int i;
    float o;
};

int main()
{
    test p;
    printf("%d",*(((char*)&p)+sizeof(double)));
}