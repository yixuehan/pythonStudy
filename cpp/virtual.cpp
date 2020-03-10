#include <iostream>
#include <memory>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

class A
{
public:
    virtual void func1()
    {
        cout << "virtual A::func1\n";
    }
    void func2()
    {
        cout << "A::func2\n";
    }
};

class B : public A
{
    void func1() override
    {
        cout << "virtual B::func1\n";
    }
    void func2()
    {
        cout << "B::func2\n";
    }
};


int main()
{
    shared_ptr<B> pB(new B);
    shared_ptr<A> pA (pB);
    pA->func1();
    pA->func2();
}
