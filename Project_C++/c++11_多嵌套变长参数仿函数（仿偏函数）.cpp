#include <tuple>
#include <string>

using namespace std;

class Table{
public:
    Table(const string & name) {}
    //key
    template <typename> class Key;
    template <typename ...Keys>
    class Key <tuple<Keys...>> {
    public:
        Key(const tuple<Keys...> &keys){}
        //value
        template <typename> class Value;
        template <typename ...Values>
        class Value <tuple<Values...>> {
        public:
            Value(const tuple<Values...> &values){}
        };
        template <typename...Values>
        Value<tuple<Values...>> operator()(Values...values){
            return Value<tuple<Values...>>(make_tuple(values...));
        }
    };
    template <typename...Keys>
    Key<tuple<Keys...>> operator()(Keys...keys){
        return Key<tuple<Keys...>>(make_tuple(keys...));
    }
};

int main()
{
    Table("aa")(8)("tfv");
}