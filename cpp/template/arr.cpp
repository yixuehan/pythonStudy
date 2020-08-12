#include <iostream>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

// template <typename T>
// struct get_array
// {
//     using type = typename std::remove_all_extents<T>::type;
//     static constexpr int size = sizeof(T) / sizeof(typename std::remove_all_extents<T>::type);
//     static constexpr int length = sizeof(T);
// };
//
template <typename T> struct get_array;

template <typename T, size_t N>
struct get_array<T[N]>
{
    using type = T;
    static constexpr int size = N;
    static constexpr int length = sizeof(T) * N;

};

int main()
{
    int a[16];
    cout << is_same<int, get_array<decltype(a)>::type>::value << endl;
    cout << get_array<decltype(a)>::size << endl;
    cout << get_array<decltype(a)>::length << endl;
}
