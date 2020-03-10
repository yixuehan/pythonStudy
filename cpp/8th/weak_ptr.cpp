#include <iostream>
#include <memory>
using namespace std;

int main()
{
    shared_ptr<int> p1(new int);
    auto p2 = p1 ;
    weak_ptr<int> wp1(p1);
    cout << wp1.use_count() << endl;
    auto p3 = wp1.lock();
    cout << wp1.use_count() << endl;

}
