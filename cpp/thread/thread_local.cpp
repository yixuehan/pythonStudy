#include <iostream>
#include <thread>
using namespace std;

class A
{
public:
    A()
    {
        cout << "A::A" << endl;
    }
    ~A()
    {
        cout << "A::~A" << endl;
    }
    void get()
    {
        cout << "A::get" << endl;
    }
};

thread_local A a;

int main()
{
    a.get();
    thread t([]{
            a.get();
            });
    t.join();
}

