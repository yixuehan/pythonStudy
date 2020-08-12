#include <iostream>
#include <memory>
using namespace std;

struct A
{
    int a[10];
};

int main()
{
    auto ptr = shared_ptr<char>(new char[sizeof(A)]);
    // cout << ptr.size() << endl;
    shared_ptr<A> pA;
    pA.swap(ptr);

}
