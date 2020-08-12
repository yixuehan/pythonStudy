#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
using namespace std;
using namespace std::chrono;

#include <boost/timer/timer.hpp>
using namespace boost;

mutex mtx;

class Mutex
{
public:
    void lock()
    {
        cout << "Mutex::lock\n";
        return mtx_.lock();
    }
    void unlock()
    {
        cout << "Mutex::unlock\n";
        return mtx_.unlock();
    }
    bool try_lock()
    {
        cout << "Mutex::try_lock\n";
        return mtx_.try_lock();
    }
    auto native_handle()
    {
        return mtx_.native_handle();
    }
public:
    std::mutex mtx_;
};

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
    // thread t1(foo1);
    // foo2();

    // t1.join();
    // Mutex my_mtx;
    bool r = false;
    // std::unique_lock<Mutex> lck(my_mtx);
    std::cout << "main unique lock\n";
    std::thread t([&]{
            std::unique_lock<mutex> lck2(mtx);
            // if (lck2.try_lock()) {
            //     cout << "thread lock success\n";
            //     lck2.unlock();
            // }
            std::cout << "thread unique lock\n";
            std::condition_variable cond;
            cout << "wait_for\n";
            cond.wait_for(lck2, chrono::seconds(3));
            // std::this_thread::sleep_for(3s);
            cout << "thread return:" << r << "\n";
            });
    {
        std::unique_lock<mutex> lck(mtx);
        std::condition_variable cond;
        cond.wait_for(lck, chrono::seconds(1), [&r]{
                return r;
                });
    }
    // if (lck.try_lock()) {
    //     cout << "lock success\n";
    //     lck.unlock();
    // }
    // else {
    //     cout << "lock fail\n";
    // }
    std::cout << "返回" << r << "\n";
    t.join();
}
