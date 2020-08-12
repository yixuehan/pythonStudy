#include <iostream>
using namespace std;

class A
{
public:
    A():_x(10){}
    void print()
    {
        cout << "A::print" << endl;
    }

    void foo()
    {
        cout << "A:" << _x << endl;
        print();
    }

    void fn()
    {
        printObj();
    }

    void printObj()
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

    void fn()
    {
        printObj();
    }

    // void foo()
    // {
    //     cout << _x << endl;
    // }


    void printObj()
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
