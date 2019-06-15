%:include <iostream>
 
struct X
<%
    compl X() <%%> // 析构函数
    X() <%%>
    X(const X bitand) = delete; // 复制构造函数
 
    bool operator not_eq(const X bitand other)
    <%
       return this not_eq bitand other;
    %>
%>;
 
int main(int argc, char* argv<::>) 
<%
    // 带引用捕获的 lambda
    auto greet = <:bitand:>(const char* name)
    <%
        std::cout << "Hello " << name
                  << " from " << argv<:0:> << '\n';
    %>;
 
    if (argc > 1 and argv<:1:> not_eq nullptr) <%
        greet(argv<:1:>);
    %>
%>