#include <iostream>
#include <tuple>
using namespace std;

template <typename ... Args>
void testArgs(Args &... args)
{
    std::tuple<Args&...> t(args...);
    std::cout << std::get<string&>(t) << std::endl;
    std::cout << std::get<sizeof...(args)-1>(t) << std::endl;
}

int main()
{
    int a = 1;
    int c = 123;
    double b = 1.23;
    string str = "abc";
    testArgs(a, c, str);
}
