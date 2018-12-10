#include <iostream>
#include <atomic>
#include <thread>
using namespace std;

int main()
{
    atomic_flag flag = ATOMIC_FLAG_INIT;
    cout << flag.test_and_set(memory_order_acquire) << "\n";
    thread t = thread([&flag]{
            cout << flag.test_and_set(memory_order_acquire) << "\n";
            });
    t.join();
}
