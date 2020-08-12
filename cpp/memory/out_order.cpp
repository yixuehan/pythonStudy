#include <iostream>
#include <thread>
using namespace std;

int x, y;

void fn1()
{
    y = 1;
    x = 2;
    cout << "x = " << x << " y = " << y << endl;
}

void fn2()
{
    while (2 != x) {
    }
    cout << "while" << endl;
    while(1 != y) {
    }
}

int main()
{
    thread t2(fn2);
    thread t1(fn1);
    t1.join();
    t2.join();
}
