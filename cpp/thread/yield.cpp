#include <iostream>
// #include <thread>
#include <chrono>
using namespace std;

#include <boost/timer/timer.hpp>
#include <boost/thread.hpp>
using namespace boost;

int main()
{
//    while(true) std::this_thread::yield();
    // this_thread::sleep_for(2s);
    cout << boost::thread::physical_concurrency() << endl;
    cout << boost::thread::hardware_concurrency() << endl;
}
