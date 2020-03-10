#include <iostream>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

struct A
{
    int a;
    int b;
    char c;
};

struct B : public A
{
    char *p;
};

int main()
{
    cout << std::is_pod<A>::value << endl;
    cout << std::is_pod<B>::value << endl;
    cout << std::is_pod<string>::value << endl;
    if constexpr (std::is_pod<A>::value) {
        cout << "pod" << endl;
    } else {
        cout << "not pod" << endl;
    }
}
