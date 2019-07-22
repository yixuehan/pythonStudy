#include <iostream>
using namespace std;

template <typename ... Ts>
auto sum(Ts ... ts)
{
    return ( 0 + ... + ts);
}

int main()
{
    cout << sum(10, 20.0123, 30) << endl;
    cout << sum() << endl;
    //cout << sum("abc"s, "wofjew", "owpfe") << endl;
}
