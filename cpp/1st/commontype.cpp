#include <iostream>
#include <type_traits>
using namespace std;

int main()
{
    cout << typeid(double).hash_code() << endl;
    cout << typeid(double).name() << endl;
    cout << typeid(common_type<double, int, float>::type).hash_code() << endl;
    cout << typeid(common_type<double, int, float>::type).name() << endl;
}
