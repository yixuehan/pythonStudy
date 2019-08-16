#include <iostream>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;


class A
{
public:
    A(){}
    virtual void print()
    {
        cout << "A::print" << endl;
    }

    void foo()
    {
        print();
    }
};

class B : public A
{
public:
    B() {}

    void print()
    {
        cout << "B::print" << endl;
    }

};

int main()
{
    B b;
    b.foo();
}
