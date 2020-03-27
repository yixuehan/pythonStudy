#include <iostream>
#include <thread>
#include <sstream>
using namespace std;

#include <boost/timer/timer.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio.hpp>
using namespace boost;

asio::io_context io_context{1};

void func(int i)
{
    stringstream ss;
    ss << "thread id:" << this_thread::get_id() << ":" << "i = " << i << endl;
    // cout << ss.str();
}

thread_local int times = 0;

asio::steady_timer steady_timer(io_context);
// asio::steady_timer timer_stop(io_context);

void post_func()
{
    // this_thread::sleep_for(1s);
    // cout << "执行函数:post_func" << endl;

    while (times < 100000) {
        // asio::post(io_context, std::bind(func, times));
        steady_timer.async_wait(std::bind(func, times));
        ++times;
    }
}

int main()
{
    steady_timer.expires_after(1s);
    // asio::ip::tcp::socket socket(io_context);
    // char buf[1024];
    // asio::async_write(socket, asio::buffer(buf), [](const boost::system::error_code &, size_t){ });
    // asio::async_read(socket, asio::buffer(buf), [](const boost::system::error_code &, size_t){ });
    // socket.async_read_some(asio::buffer(buf), [](const boost::system::error_code &, size_t){ });
    // timer_stop.expires_after(2s);
    // timer_stop.async_wait(std::bind(&asio::io_context::stop, &io_context));
    // timer_stop.async_wait([&io_context]()mutable{
    //         io_context.stop();
    //         }
    //         );
    thread threads[100];
    for (int i = 0; i < 100; ++i) {
        threads[i] = thread(post_func);
    }
    // cout << (void*)count << endl;
    // asio::io_context::work work(io_context);
    // asio::steady_timer timer(5);
    // work.get_io_context().
    // timer.async_wait()
    
    this_thread::sleep_for(1ms);
    // io_context.poll_one();
    // io_context.run_one();
    // io_context.poll();
    io_context.run();
    for (int i = 0; i < 100; ++i) {
        threads[i].join();
    }
}
