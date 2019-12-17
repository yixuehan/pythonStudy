#include <iostream>
#include <thread>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

int main()
{
    while(true) std::this_thread::yield();
}
