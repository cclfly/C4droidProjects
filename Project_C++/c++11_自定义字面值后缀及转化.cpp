//自定义字面值转换

#include <iostream>

using namespace std;

struct watt {unsigned int p;};

watt operator "" _w(unsigned long long p)
{
    cout<< p <<endl;
    return watt{p};
}

int main()
{
    watt p1 = 52348_w;
    cout<< p1.p <<endl;
    watt p2 = 5234288885555555555555555558_w;
    cout<< p2.p <<endl;
    return 0;
}