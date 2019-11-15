#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

mutex mtx;

void foo1()
{
    mtx.lock();
    mtx.lock();
}

void foo2()
{
    mtx.unlock();
    mtx.unlock();
}

int main()
{
    thread t1(foo1);
    foo2();

    t1.join();
}
