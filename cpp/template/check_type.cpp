#include <iostream>
#include <type_traits>
#include <functional>
using namespace std;

void func(int a)
{
}

int main()
{
    auto lambda = []{};
    auto func_bind = bind(&func, 10);
    cout << "is_function:" << is_function<decltype(lambda)>::value << std::endl;
    cout << "is_function:" << is_function<decltype(func)>::value << std::endl;
    cout << "is_function:" << is_function<decltype(func_bind)>::value << std::endl;
    // invocable
    cout << "invocable" << endl;
    // cout << is_invocable<int>(func)
}
