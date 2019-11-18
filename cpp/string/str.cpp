#include <stdio.h>
#include <iostream>
using namespace std;

template <typename T>
struct C4
{
    const T (*ch)[4];
    using c4_t = decltype(*ch);
};

int main()
{
    cout << std::is_same<decltype("abc"), char [4]>::value  << endl;
    cout << std::is_same<decltype("abc"), const char [4]>::value  << endl;
    cout << std::is_same<decltype("abc"), char *>::value  << endl;
    cout << std::is_same<decltype("abc"), const char *>::value  << endl;
    cout << std::is_same<decltype("abc"), char (*)[4]>::value  << endl;
    cout << std::is_same<decltype("abc"), const char (*)[4]>::value  << endl;
    auto p1 = "abc";
    decltype("abc") p2 = "abc";
    const char (*ch)[4] = {};
    cout << std::is_same<decltype(p1), decltype(p2)>::value  << endl;
    cout << std::is_same<decltype("abc"), decltype(p2)>::value  << endl;
    cout << std::is_same<decltype("abc"), decltype(*ch)>::value  << endl;
    cout << std::is_same<decltype("abc"), C4<char>::c4_t>::value  << endl;
}
