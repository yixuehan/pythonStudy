#include <iostream>
#include <string_view>
using namespace std;

int main()
{
    auto a("abcdef"s);
    auto b ("123456"sv);
    string_view c("1234567890", 3);
    cout << (void*)"123456" << endl; 
    cout << (void*)b.data() << endl;
    cout << a << ' ' << b << ' ' << c << endl;
    cout << c.data() << endl;
}
