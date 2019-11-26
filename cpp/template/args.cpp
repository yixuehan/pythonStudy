#include <iostream>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

template < typename T, typename ... Ts >
void printf3(T &&value, Ts &&... args)
{
    cout << value << ' ';
    if constexpr(sizeof...(args) > 0) {
        printf3(std::forward<Ts>(args)...);
    }
}
void test_lambda()
{
 printf3(1, 2, 3);
}

int main()
{
    test_lambda();
}
