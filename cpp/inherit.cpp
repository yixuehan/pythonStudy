#include <iostream>
using namespace std;

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

    virtual void fn()
    {
        printObj();
    }

    static void printObj()
    {
        cout << "obj a" << endl;
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

    virtual void fn()
    {
        printObj();
    }


    static void printObj()
    {
        cout << "obj b" << endl;
    }

};

int main()
{
    B b;
    b.foo();
    b.fn();
}
