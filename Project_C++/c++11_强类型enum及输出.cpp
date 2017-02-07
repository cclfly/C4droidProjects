#include <iostream>

using namespace std;

enum class sex{
    boy,
    girl
};

ostream & operator<<(ostream & out, sex s)
{
    if (s == sex::boy)
        out<<"男";
    else
        out<<"女";
    return out;
}

int main()
{
    cout<<sex::boy<<endl;
}