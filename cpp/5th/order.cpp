#include <iostream>
#include <thread>
#include <atomic>
using namespace std;

//#define _GNU_SOURCE
//#include <sched.h>
#include <unistd.h>
#include <pthread.h>

//atomic<int> X, Y;
int X, Y;
int r1, r2;

void thread1()
{
    X = 1;
    r1 = Y;
}

void thread2()
{
    Y = 1;
    r2 = X;
}

//atomic<int> a;
int a;
int b;

void threada()
{
    auto thread_id = pthread_self();
    cpu_set_t get;
    CPU_ZERO(&get);
    CPU_SET(0, &get);
    if (pthread_setaffinity_np(thread_id, sizeof(get), &get)) {
        cout << "threada error\n";
        exit(1);
    }
    CPU_ZERO(&get);
    if (pthread_getaffinity_np(thread_id, sizeof(get), &get)) {
        cout << "threada error\n";
        exit(1);
    }
    for (int i = 0; i < 4; ++i) {
        if (CPU_ISSET(i, &get)) {
            cout << "threada cpu:" << i << "\n";
        }
    }
    b = 1;
    //a.store(1, memory_order_release);
    a = 1;
    cout << "threada id:" << this_thread::get_id() << "\n";
}

void threadb()
{
    auto thread_id = pthread_self();
    cpu_set_t get;
    CPU_ZERO(&get);
    CPU_SET(0, &get);
    if (pthread_setaffinity_np(thread_id, sizeof(get), &get)) {
        cout << "threada error\n";
        exit(1);
    }
    CPU_ZERO(&get);
    if (pthread_getaffinity_np(thread_id, sizeof(get), &get)) {
        cout << "threada error\n";
        exit(1);
    }
    for (int i = 0; i < 4; ++i) {
        if (CPU_ISSET(i, &get)) {
            cout << "threadb cpu:" << i << "\n";
        }
    }
    //while(a.load(memory_order_acquire) != 1) cout << "a:" << a << "\n";
    cout << "threadb id:" << this_thread::get_id() << "\n";
    while(a != 1) ;
    cout << b << "\n";
}

int main()
{
    while (1) {
        X = 0;
        Y = 0;
        thread t1(thread1);
        thread t2(thread2);
        t1.join();
        t2.join();
        cout << r1 << " " << r2 << "\n";
        if (r1 == r2 && r1 == 0) {
            break;
        }
    }

    thread ta(threada);
    thread tb(threadb);
    ta.join();
    cout << "threada:" << a << "\n";
    cout << "threada end\n";
    tb.join();

}
