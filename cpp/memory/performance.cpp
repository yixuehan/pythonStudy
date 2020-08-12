#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

volatile int v_x = 0;
int64_t x = 0;
atomic<int> a_x(0);
int lock_x = 0;

constexpr int NUM = 10000;

template <typename Data>
void fn_add_load(Data &data)
{
    for (int i = 0; i < NUM; ++i) {
        for (int j = 0; j < NUM; ++j) {
            data.fetch_add(1, memory_order_relaxed);
        }
    }
}


template <typename Data>
void fn_add(Data &data)
{
    for (int i = 0; i < NUM; ++i) {
        for (int j = 0; j < NUM; ++j) {
            ++data;
        }
    }
}

mutex g_mtx;
template <typename Data>
void fn_add_lock(Data &data)
{
    for (int i = 0; i < NUM; ++i) {
        for (int j = 0; j < NUM; ++j) {
            g_mtx.lock();
            ++data;
            g_mtx.unlock();
        }
    }
}

template <typename Data, typename Fn>
void fn_thread_impl(Data &data, Fn &&fn) {
    thread t1(fn, std::ref(data));
    thread t2(fn, std::ref(data));
    t1.join();
    t2.join();
}

template <typename Data, typename Fn = decltype(fn_add<Data>)>
void fn_thread(Data &data, Fn &&fn = fn_add<Data>) {
    thread t1(fn, std::ref(data));
    thread t2(fn, std::ref(data));
    t1.join();
    t2.join();
}


int main()
{
    {
        timer::auto_cpu_timer t;
        fn_thread(v_x);
        printf("%d\n", v_x);
    }
    {
        timer::auto_cpu_timer t;
        fn_thread(a_x);
        printf("%d\n", a_x.load());
    }
    {
        timer::auto_cpu_timer t;
        fn_thread(x);
        printf("%ld\n", x);
    }
    {
        timer::auto_cpu_timer t;
        fn_thread(lock_x, fn_add_lock<int>);
        printf("%d\n", lock_x);
    }
    {
        timer::auto_cpu_timer t;
        fn_thread(a_x, fn_add_load);
        printf("%d\n", lock_x);
    }

}
