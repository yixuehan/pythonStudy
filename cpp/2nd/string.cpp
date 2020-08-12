#include <iostream>
using namespace std;

template <typename T>
class My
{
public:
    My(T t)
    {
        _t = t;
    }
    //My(const T &th)
    //    :_t(th._t)
    //{}
    void print()
    {
        cout << typeid(_t).name() << endl;
    }

private:
    T _t;
};

My(char const*) -> My<string>;
//My(char const*&) -> My<string>;

int main()
{
    My("abc").print();
    My(string("abc")).print();
    My m1{"123"};
    m1.print();
    My m2{"456"};
    m1 = m2;
}
