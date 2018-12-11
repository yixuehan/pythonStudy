#include <iostream>
#include <utility>
#include <atomic>

struct A { int a[100]; };
struct B { int x, y; };
struct C { A a;} ;
int main()
{
    std::cout << std::boolalpha
              << "std::atomic<A> is lock free? "
              << std::atomic<A>{}.is_lock_free() << '\n'
              << "std::atomic<B> is lock free? "
              << std::atomic<B>{}.is_lock_free() << '\n'
              << "std::atomic<C> is lock free? "
              << std::atomic<C>{}.is_lock_free() << '\n';
}
