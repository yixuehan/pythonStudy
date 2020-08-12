#include <iostream>
#include <memory>
using namespace std;

void free_mem(int *p)
{
    if (p) {
        printf("free_mem:%d\n", *p);
        delete p;
    }
    else {
        printf("free_mem null\n");
    }
}

class A
{
public:
    A(){
        cout << "构造A\n";
    }
    ~A() {
        cout << "析构A\n";
    }
};

int main()
{
    shared_ptr<int> ptr(new int(10), free_mem);
    ptr.reset(new int(100), free_mem);
    ptr.reset((int*)nullptr, free_mem);
    ptr.reset(new int(1000));
    ptr.reset(new int(10000));
    shared_ptr<A[]> ptrA(new A[10]);

}
