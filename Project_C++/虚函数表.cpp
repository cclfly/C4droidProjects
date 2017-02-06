#include<cstdio>

class test
{
    public:
    test():k(9.9),i(9),o(9.f){};
    private:
    double k;
    int i;
    float o;
    virtual void p()
    {
        printf("test::p(),i=%d\n",i);
    }
};

int main()
{
    test p;
    ((void(***)(test&))&p)[0][0](p);
    printf("%d",*(((char*)&p)+sizeof(double)+8));
}