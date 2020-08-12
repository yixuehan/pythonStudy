#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

#include <boost/timer/timer.hpp>
#include <boost/asio.hpp>
using namespace boost;

void func(int x, int y)
{
    cout << x << ":" << y << endl;
}

void foo()
{
    cout << "foo\n";
}

void bar()
{
    cout << "bar\n";
}

void timer_func()
{
}

class TaskQueue
{
public:
    TaskQueue()
        :_io_context{}
        ,_work_guard(asio::make_work_guard(_io_context))
    {
    }

    asio::io_context::count_type run()
    {
        return _io_context.run();
    }

    void thread_run()
    {
        _thread = std::thread([this]{
                _io_context.run();
        });
    }

    void stop()
    {
        return _io_context.stop();
    }

    ~TaskQueue()
    {
        _work_guard.reset();
        if (_thread.joinable()) {
            _thread.join();
        }
    }
    template <typename Rep, typename Period, typename Func, typename ...Args>
    void append(std::chrono::duration<Rep, Period> &&timeout, Func &&func, Args &&...args)
    {
        auto timer_ptr = std::make_shared<asio::steady_timer>(_io_context, timeout);
        auto call_obj = std::bind(std::forward<Func>(func), std::forward<Args>(args)...);
        timer_ptr->async_wait([call_obj, timer_ptr](const boost::system::error_code &){
                cout << "执行定时任务" << endl;
                call_obj();
                }
                );
    }

    template <typename Func, typename ...Args>
    void append(Func &&func, Args &&...args)
    {
        asio::dispatch(_io_context, std::bind(func, std::forward<Args>(args)...));
    }
private:
    asio::io_context _io_context;
    asio::executor_work_guard<asio::io_context::executor_type> _work_guard;
    std::thread _thread;
private:
    TaskQueue(const TaskQueue &) = delete;
    TaskQueue &operator=(const TaskQueue &) = delete;
};

void heartbeat(TaskQueue &q)
{
    cout << "heartbeat\n";
    q.append(2s, heartbeat, std::ref(q));
}

int main()
{
    TaskQueue q;
    q.thread_run();
    q.append(func, 10, 20);
    int x = 100, y = 200;
    q.append(func, x, y);
    q.append(foo);
    q.append(bar);
    q.append(2s, bar);
    heartbeat(q);
    // q.append(2s, heartbeat, q);
    cout << "append end..." << endl;
    // std::this_thread::sleep_for(10s);
    // cout << "sleep end..." << endl;
    // q.run();
}
