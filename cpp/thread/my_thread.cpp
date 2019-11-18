#include <iostream>
#include <functional>
#include <thread>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

void *pFunc(void* arg)
{
    auto func = (function<void()>*)arg;
    (*func)();
    return nullptr;
}

class MyThread
{
    using PFunc = void *(void*);
public:
    template <typename Fn, typename ...Args>
    MyThread(Fn &&fn, Args &&... args)
    {
        _fn = std::bind(fn, std::forward<Args>(args)...);
    }
    void run()
    {
        // _t = std::thread(_fn);
        pthread_create(&tid, nullptr, pFunc, &_fn);

    }
    ~MyThread()
    {
        // if (_t.joinable()) {
        //     _t.join();
        // }
        // if (pthread_joinable(tid)) {
            pthread_join(tid, nullptr);
        // }
    }
private:
    function<void()> _fn;
    // std::thread _t;
    pthread_t tid;
    PFunc _pfunc;
};


void func()
{
    cout << "test thread\n";
}

void func2(int a)
{
    cout << "a:" << a << endl;
}

int main()
{
    MyThread t(func);
    MyThread t2(func2, 100);
    t.run();
    t2.run();
}
