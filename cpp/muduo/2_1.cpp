#include <iostream>
#include <mutex>
#include <vector>
#include <cassert>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

struct Foo
{
    void doit(){}
};

mutex mtx;
vector<Foo> foos;

void postNoLock(const Foo &f)
{
    assert(!mtx.try_lock());
    foos.push_back(f);
}

void post(const Foo & f)
{
    lock_guard<mutex> lck(mtx);
    postNoLock(f);
}

void traverse()
{
    lock_guard<mutex> lck(mtx);
    for (auto &foo : foos) {
        foo.doit();
    }

}

int main()
{
}
