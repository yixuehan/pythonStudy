#include <iostream>
#include <array>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

template <int M, int N>
void printSize(int arr[M][N])
{
    cout << M << ":" << N << endl;
}

int main()
{
    int arr[10][20];
    printSize(arr);
}
