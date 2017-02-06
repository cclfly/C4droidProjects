#include <iostream>
using namespace std;
class aa
{
  public:
    int aaa = 0;
};
template < class charT, class traits >
    std::basic_ostream < charT, traits > &a (std::basic_ostream < charT, traits > &strm)
{
    strm.put (strm.widen ('\n'));
    strm.flush ();
    return strm;
}

int main ()
{
    aa A;
    cout<<a;
    return 0;
}