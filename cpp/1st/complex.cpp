#include <iostream>
#include <complex>
//#include <typeinfo>
using namespace std;

namespace std {
    template <typename T>
    bool operator<(const std::complex<T> &c1, const std::complex<T> &c2)
    {
        if (c1.real() < c2.real())
            return true;
        if (c1.real() == c2.real() && c1.imag() <= c2.imag())
            return true;
        return false;
    }
}

template <typename T1, typename T2>
std::common_type_t<T1, T2> my_max(T1 a, T2 b)
{
    return a > b ? a : b;
}

int main()
{
    std::complex<float> c1(2,1), c2(1,2);
    cout << std::max(c1, c2) << endl;
    int a = 30;
    double b = 20.0;
    int &ra = a;
    double &rb = b;
    cout << typeid(my_max(a, b)).name() << endl;
    cout << typeid(my_max(ra, rb)).name() << endl;
}
