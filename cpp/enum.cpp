#include <iostream>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;



enum class Color : uint8_t
{
    red = 0,
    green = 1,
    blue = 2,
};

int main()
{
    cout << sizeof(Color) << endl;
}
