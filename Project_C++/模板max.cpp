#include <iostream>

template <int i>
class Max{
public:
    static int _(int* A){
    	int t=Max<i-1>::_(A);
    	return t>A[i]?t:A[i];
    }
};

template <>
class Max<0>{
public:
	static int _(int* A){ return A[0]; }
};

int main(){
	int t[5]={14, 6, 3, 7, 1};
	std::cout << Max<4>::_(t);
}
//最终改修版