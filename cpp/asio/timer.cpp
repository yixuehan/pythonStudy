#include <iostream>
#include <thread>
using namespace std;

#include <boost/timer/timer.hpp>
#include <boost/asio.hpp>
using namespace boost;

int main()
{
    asio::io_context io_context;
    asio::steady_timer timer1(io_context, 2s);
    timer1.async_wait([&io_context](const boost::system::error_code &ec){
            cout << "2s时间到\n";
            // io_context.stop();
            // io_context.dispatch
            });

    std::thread t([&io_context]{
            io_context.run();
            cout << "退出事件循环\n";
            });

    asio::steady_timer timer2(io_context, 10s);
    timer2.async_wait([](const boost::system::error_code &ec){
            cout << "3s时间到\n";
            });

    t.join();
    // io_context.run();
    // this_thread::sleep_for(5s);
    // cout << "继续事件循环\n";
    // io_context.run();
}
