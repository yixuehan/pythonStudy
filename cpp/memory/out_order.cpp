#include <iostream>
#include <atomic>
#include <thread>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

// atomic<int> x, y;
volatile int x, y;

void fn1()
{
    y = 1;
    x = 2;
    // cout << x << ":" << y << endl;
}

void fn2()
{
    while (2 != x) {
//         int t = 1;
//         int w = t;
        // cout << t << endl;
        // cout << "x=" << x << endl;
    }
    cout << "while" << endl;
    while(1 != y) {
        // cout << "y=" << y << endl;
    }
//     cout << "end" << endl;
}

int main()
{
    thread t1(fn1);
    thread t2(fn2);
    t1.join();
    t2.join();
}
