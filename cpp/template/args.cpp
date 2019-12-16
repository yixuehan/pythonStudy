#include <iostream>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

/*
template < typename T, typename ... Ts >
void printf3(T &&value, Ts &&... args)
{
    cout << value << ' ';
    if constexpr(sizeof...(args) > 0) {
        printf3(std::forward<Ts>(args)...);
    }
}
*/

template < typename ... Ts >
auto printf3(Ts &&... args) ->void
{
       // std::cout << value << std::endl;
    
    std::initializer_list <int> {([](auto arg) {
             std::cout << arg << std::endl;
    }(args), 0) ...};

}

void test_lambda()
{
 printf3(1, 2, 3.12);
}

int main()
{
    test_lambda();
}
