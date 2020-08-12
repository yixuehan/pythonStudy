#include <iostream>
#include <future>
#include <functional>
#include "util/defer.h"
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

/*
class Defer {
public:
    Defer(){}

    template <typename Func, typename ...Args>
    Defer(Func &&f, Args &&...args)
        :_f(std::bind(std::forward<Func>(f), std::forward<Args>(args)...))
    {
    }

    template <typename Func, typename ...Args>
    void reset(Func &&f, Args &&...args)
    {
        _f = std::bind(std::forward<Func>(f), std::forward<Args>(args)...);
    }

    ~Defer()
    {
        _f();
    }
private:
    function<void()> _f;
};
*/

template <typename Class>
class Single
{
public:
    std::shared_ptr<Class> operator->()
    {
        static std::shared_ptr<Class> ptr = std::make_shared<Class>();
        return ptr;
    }
};

class A
{
public:
    A()
    {
        Defer f([](){
                });
        std::cout << "A contruce\n";
    }
    void print()
    {
        std::cout << (void*)this << endl;
    }
};


void test_defer(int &res)
{
    int x = 10;
    Defer f ([&]{
            cout << "defer modify res\n";
            x = 20;
            res = x;
            cout << "defer modify res after\n";
            });
    cout << "modify res\n";
    res = x;
    cout << "modify res after\n";
    // f.get();
}

void func(int &a)
{
    cout << "func:" << a << endl;
}

int main()
{
    int a = 0;
    test_defer(a);
    cout << "a:" << a << endl;
    shared_ptr<int> ptr(nullptr, [&](int*){
            func(a);
            });
    a = 22;
    Defer f(func, a);
    Single<A> a1;
    a1->print();
    Single<A> a2;
    a2->print();
    std::thread t1([]{
        Single<A> a3;
        a3->print();
            });
    t1.join();
}
