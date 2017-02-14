#include <iostream>
#include <tuple>

using namespace std;

template<typename T1, typename T2>
class S {
public:
    S(const T1 &t1, const T2 &t2){
        cout<<"1"<<endl;
    }
};

template<
    template<typename...> class T1, typename...Args1,
    template<typename...> class T2, typename...Args2>
class S <T1<Args1...>,T2<Args2...>> {
public:
    S(T1<Args1...>,T2<Args2...>){
        cout<<"2"<<endl;
    }
};

int main()
{
    S<tuple<int,float,char>, tuple<bool,double>>
        s{
            make_tuple(1, 2.3f, 'a'),
            make_tuple(false, 8.8)
        };
}