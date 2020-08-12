#include <iostream>
#include <array>
#include <memory>
#include <string.h>
using namespace std;

// #include <boost/timer/timer.hpp>
// using namespace boost;

template <int M, int N>
void printSize(int arr[M][N])
{
    cout << M << ":" << N << endl;
}

auto get_array()
{
    // static shared_ptr<char []> big_array(new char[500 * 1024 * 1024]);
    // static std::array<int, 500 * 1024 * 1024> big_array;
    static int big_array[500 * 1024 * 1024];
    // memset(big_array, 0, sizeof(big_array));
    return big_array;
}

int main()
{
    //  int arr[10][20];
    // int big_array[50 * 1024 * 1024] = {0};
    // int big_array[5] = {0};
    // cout << sizeof(big_array) << endl;
    // printSize(arr);
    get_array();
}
