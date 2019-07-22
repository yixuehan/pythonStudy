#include <iostream>
#include <tuple>
#include <utility>
 
int add(int first, int second) { return first + second; }
 
template<typename T>
T add_generic(T first, T second) { return first + second; }
 
auto add_lambda = [](auto first, auto second) { return first + second; };
 
int main()
{
    // OK
    std::cout << std::apply(add, std::make_pair(1, 2)) << '\n';
 
   // 错误：无法推导函数类型
   std::cout << std::apply(add_generic, std::make_pair(2.0f, 3.0f)) << '\n'; 
 
   // OK
   std::cout << std::apply(add_lambda, std::make_pair(2.0f, 3.0f)) << '\n'; 
}
