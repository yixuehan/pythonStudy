#include <iostream>
using namespace std;

int main()
{
    auto s = string("hello").c_str();
    string("world");
    cout << s << endl;
}
