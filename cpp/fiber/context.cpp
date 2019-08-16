#include <iostream>
using namespace std;

#include <boost/timer/timer.hpp>
#include <boost/context/fiber.hpp>
using namespace boost;

namespace ctx = boost::context;

ctx::fiber func(ctx::fiber &&sink, int &a)
{
    a = 0;
    int b = 1;
    for (;;) {
        cout << "func before resume:" << a << endl;
        getchar();
        sink = std::move(sink).resume();
        cout << "func after resume:" << a << endl;
        int next = a + b;
        a = b;
        b = next;
    }
    return std::move(sink);
}

int main()
{
    int a;
    ctx::fiber source(std::bind(func, std::placeholders::_1, std::ref(a)));
    for (int i = 0; i < 10; ++i) {
        cout << "main before resume:" << a  << endl;
        source = std::move(source).resume();
        std::cout << "main after resume:" << a << endl ;
    }
}
