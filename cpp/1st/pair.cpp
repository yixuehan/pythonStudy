#include <iostream>
using namespace std;

int main()
{
    std::pair<int, int> a(10, 20);
    cout << a.first << ' ' << a.second << endl;
    auto [x,y] = a;
    cout << x << ' ' << y << endl;

}
