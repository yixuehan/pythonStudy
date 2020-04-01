#include <iostream>
#include <thread>
#include <sstream>
using namespace std;

#include <boost/timer/timer.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio.hpp>
using namespace boost;

asio::io_context io_context;

void func(int i)
{
    stringstream ss;
    ss << "thread id:" << this_thread::get_id() << ":" << "i = " << i << endl;
    cout << ss.str();
}

thread_local int times = 0;

void post_func()
{
    cout << "执行函数:post_func" << endl;

    while (times < 100000) {
        asio::post(std::bind(func, times));
        ++times;
    }
}

int main()
{
    auto t1 = thread(post_func);
    auto t2 = thread(post_func);
    this_thread::sleep_for(1ms);
    io_context.run();
    t1.join();
    t2.join();
}
