#include<iostream>
#include<climits>
union shit
{
    int i;
    float f;
};
using namespace std;
int main(void)
{
    shit fuck;
    fuck.i=100;
    int flag=1;
    cout<<"shit 里面的二进制是"<<endl;
    for(int i=0;i<sizeof(int)*CHAR_BIT;i++)//这个循环用于显示int的二进制码
        cout<<((fuck.i&flag<<sizeof(int)*CHAR_BIT-1-i)>>sizeof(int)*CHAR_BIT-1-i);
    cout<<endl<<"把此二进制当做int解释是"<<endl<<fuck.i
            <<endl<<"把此二进制当做float解释是"<<endl<<fuck.f;
}