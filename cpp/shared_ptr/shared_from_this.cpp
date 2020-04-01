#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

class A : public enable_shared_from_this<A>
{
public:
    A()
    {
        cout << "construct A\n";
    }
    std::thread run()
    {
        auto ptr = shared_from_this();
        return std::thread([ptr]{
                this_thread::sleep_for(2s); 
            });
    }
    ~A()
    {
        cout << "destory A\n";
    }
};

int main()
{
    std::thread t1;
    {
        shared_ptr<A> p1(new A);
        cout << p1.use_count() << endl;
        t1 = p1->run();
        cout << p1.use_count() << endl;
    }
    t1.join();
    // auto p2 = a.shared_from_this();
}
