#include <iostream>
using namespace std;

class A
{
public:
    A():_x(10){}
    virtual void print()
    {
        cout << "A::print" << endl;
    }

    virtual void foo()
    {
        cout << "A:" << _x << endl;
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
private:
    int _x;
};

class B : public A
{
public:
    B() :_x(20){}

    void print()
    {
        cout << "B::print" << endl;
    }

    virtual void fn()
    {
        printObj();
    }

    // void foo()
    // {
    //     cout << _x << endl;
    // }


    static void printObj()
    {
        cout << "obj b" << endl;
    }
private:
    int _x;

};

int main()
{
    B b;
    b.foo();
    b.fn();
}
