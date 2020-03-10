#include <iostream>
#include <future>
#include <functional>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

template <typename Func, typename ...Args>
class Defer {
public:
    Defer(Func &&f, Args &&...args)
        :_f(std::bind(std::forward<Func>(f), std::forward<Args>(args)...))
    {
    }
    ~Defer()
    {
        _f();
    }
private:
    function<void()> _f;
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
}
