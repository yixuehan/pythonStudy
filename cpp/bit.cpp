#include <iostream>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

int main()
{
    uint32_t a = UINT32_MAX;
    cout << a << endl;
    a >>= 1;
    cout << a << endl;
}
